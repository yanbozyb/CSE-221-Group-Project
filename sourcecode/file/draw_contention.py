import matplotlib.pyplot as plt
import numpy as np

# 数据集 data 和 data2
data = """
Process num: 1, Read time: 0.107 ms
Process num: 2, Read time: 0.109 ms
Process num: 3, Read time: 0.109 ms
Process num: 4, Read time: 0.114 ms
Process num: 5, Read time: 0.120 ms
Process num: 6, Read time: 0.130 ms
Process num: 7, Read time: 0.140 ms
Process num: 8, Read time: 0.145 ms
Process num: 9, Read time: 0.154 ms
Process num: 10, Read time: 0.164 ms
Process num: 11, Read time: 0.168 ms
Process num: 12, Read time: 0.176 ms
Process num: 13, Read time: 0.183 ms
Process num: 14, Read time: 0.191 ms
Process num: 15, Read time: 0.202 ms
Process num: 16, Read time: 0.206 ms
"""

def parse_data(dataset):
    sizes = []
    latencies = []
    for line in dataset.strip().split('\n'):
        parts = line.split(',')
        size_kb = int(parts[0].split()[2])
        latency_ms = float(parts[1].split()[2])
        sizes.append(int(size_kb))
        latencies.append(10 * latency_ms)
    return sizes, latencies

process, latencies1 = parse_data(data)

# 画图
fig = plt.figure(figsize=(5.5, 3.2))
plt.plot(process, latencies1, marker='o')
plt.xlabel('Number of Processes')
plt.ylabel('Average Latency (ms)')
plt.title('Average Per-Block (4KiB) Access Time')
plt.xticks(process, process, rotation=0)
#plt.legend()
#plt.ylim(0, 1.6)

fig.tight_layout()
plt.savefig('file_contention.pdf',dpi=300)
plt.show()