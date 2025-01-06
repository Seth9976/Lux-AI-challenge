import json
import subprocess
import sys
from typing import Dict, Any

class Agent:
    def __init__(self):
        # 启动C程序
        self.process = subprocess.Popen(
            ['./agent'],  # 确保C程序已经编译
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=1
        )
        
    def __del__(self):
        """清理进程"""
        if hasattr(self, 'process'):
            self.process.terminate()
            self.process.wait()

    def setup(self, env_cfg: Dict[str, Any], player: str):
        """初始化智能体"""
        # 发送环境配置
        self._send_message(json.dumps(env_cfg))
        # 发送玩家ID
        self._send_message(player)

    def act(self, obs: Dict[str, Any]) -> Dict[str, Any]:
        """执行动作"""
        # 发送观察数据
        self._send_message(json.dumps(obs))
        
        # 读取响应
        response = self.process.stdout.readline().strip()
        try:
            return json.loads(response)
        except json.JSONDecodeError as e:
            print(f"Error decoding response: {e}", file=sys.stderr)
            return {}

    def _send_message(self, message: str):
        """发送消息到C程序"""
        try:
            self.process.stdin.write(f"{message}\n")
            self.process.stdin.flush()
        except IOError as e:
            print(f"Error sending message: {e}", file=sys.stderr)
            raise

if __name__ == "__main__":
    def read_input():
        """读取输入直到遇到空行"""
        try:
            lines = []
            while True:
                line = input()
                if line.strip() == "":
                    break
                lines.append(line)
            return "".join(lines)
        except EOFError:
            return ""

    # 创建智能体实例
    agent = Agent()

    # 读取初始配置
    env_cfg = json.loads(read_input())
    player = input()
    
    # 设置智能体
    agent.setup(env_cfg, player)

    # 主游戏循环
    while True:
        obs = read_input()
        if not obs:
            break
            
        observation = json.loads(obs)
        actions = agent.act(observation)
        
        # 输出动作
        print(json.dumps(actions))
        print("", flush=True)
