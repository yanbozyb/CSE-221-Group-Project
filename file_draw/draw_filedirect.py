import matplotlib.pyplot as plt
import numpy as np

# 数据集 data 和 data2
data = """
File size: 4 KB, Read time: 0.039 ms
File size: 8 KB, Read time: 0.042 ms
File size: 16 KB, Read time: 0.049 ms
File size: 32 KB, Read time: 0.045 ms
File size: 64 KB, Read time: 0.052 ms
File size: 128 KB, Read time: 0.053 ms
File size: 256 KB, Read time: 0.051 ms
File size: 512 KB, Read time: 0.045 ms
File size: 1024 KB, Read time: 0.036 ms
File size: 2048 KB, Read time: 0.035 ms
File size: 4096 KB, Read time: 0.034 ms
File size: 8192 KB, Read time: 0.032 ms
File size: 16384 KB, Read time: 0.037 ms
File size: 32768 KB, Read time: 0.039 ms
File size: 65536 KB, Read time: 0.038 ms
File size: 131072 KB, Read time: 0.038 ms
File size: 262144 KB, Read time: 0.035 ms
File size: 524288 KB, Read time: 0.036 ms
File size: 1048576 KB, Read time: 0.035 ms

"""

data2 = """
File size: 4 KB, Read time: 0.038 ms
File size: 8 KB, Read time: 0.043 ms
File size: 16 KB, Read time: 0.059 ms
File size: 32 KB, Read time: 0.058 ms
File size: 64 KB, Read time: 0.054 ms
File size: 128 KB, Read time: 0.108 ms
File size: 256 KB, Read time: 0.113 ms
File size: 512 KB, Read time: 0.115 ms
File size: 1024 KB, Read time: 0.120 ms
File size: 2048 KB, Read time: 0.121 ms
File size: 4096 KB, Read time: 0.111 ms
File size: 8192 KB, Read time: 0.109 ms
File size: 16384 KB, Read time: 0.107 ms
File size: 32768 KB, Read time: 0.107 ms
File size: 65536 KB, Read time: 0.104 ms
File size: 131072 KB, Read time: 0.105 ms
File size: 262144 KB, Read time: 0.105 ms
File size: 524288 KB, Read time: 0.105 ms
File size: 1048576 KB, Read time: 0.104 ms
"""

def parse_data(dataset):
    sizes = []
    latencies = []
    for line in dataset.strip().split('\n'):
        parts = line.split(',')
        size_kb = int(parts[0].split()[2])
        latency_ms = float(parts[1].split()[2])
        sizes.append(int(np.log2(size_kb)))
        latencies.append(10 * latency_ms)
    return sizes, latencies

sizes1, latencies1 = parse_data(data)
sizes2, latencies2 = parse_data(data2)

# 画图
fig = plt.figure(figsize=(5.5, 3.2))
plt.plot(sizes1, latencies1, marker='o', label='Sequential read')
plt.plot(sizes2, latencies2, marker='x', label='Random read')
plt.xlabel('Log2 (File Access Size (KiB))')
plt.ylabel('Average Latency (ms)')
plt.title('Local Average Per-Block (4KiB) Access Time')
plt.xticks(sizes1, sizes1, rotation=0)
plt.legend()
plt.ylim(0, 1.6)

fig.tight_layout()
plt.savefig('file_direct.pdf',dpi=300)
plt.show()