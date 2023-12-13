import matplotlib.pyplot as plt
import numpy as np

data = """
File size: 1 KB, Read time: 3.113 ms
File size: 2 KB, Read time: 0.004 ms
File size: 4 KB, Read time: 0.001 ms
File size: 8 KB, Read time: 0.002 ms
File size: 16 KB, Read time: 0.002 ms
File size: 32 KB, Read time: 0.449 ms
File size: 64 KB, Read time: 1.467 ms
File size: 128 KB, Read time: 0.077 ms
File size: 256 KB, Read time: 12.135 ms
File size: 512 KB, Read time: 6.620 ms
File size: 1024 KB, Read time: 2.282 ms
File size: 2048 KB, Read time: 0.784 ms
File size: 4096 KB, Read time: 5.726 ms
File size: 8192 KB, Read time: 3.005 ms
File size: 16384 KB, Read time: 15.209 ms
File size: 32768 KB, Read time: 20.254 ms
File size: 65536 KB, Read time: 43.785 ms
File size: 131072 KB, Read time: 97.094 ms
File size: 262144 KB, Read time: 1050.603 ms
File size: 524288 KB, Read time: 2317.302 ms
File size: 1048576 KB, Read time: 4635.801 ms
"""

data2= """
File size: 1 KB, Read time: 0.011 ms
File size: 2 KB, Read time: 0.002 ms
File size: 4 KB, Read time: 0.001 ms
File size: 8 KB, Read time: 0.002 ms
File size: 16 KB, Read time: 0.009 ms
File size: 32 KB, Read time: 0.007 ms
File size: 64 KB, Read time: 0.017 ms
File size: 128 KB, Read time: 0.033 ms
File size: 256 KB, Read time: 0.123 ms
File size: 512 KB, Read time: 0.166 ms
File size: 1024 KB, Read time: 0.344 ms
File size: 2048 KB, Read time: 0.784 ms
File size: 4096 KB, Read time: 1.503 ms
File size: 8192 KB, Read time: 3.044 ms
File size: 16384 KB, Read time: 6.147 ms
File size: 32768 KB, Read time: 12.222 ms
File size: 65536 KB, Read time: 25.541 ms
File size: 131072 KB, Read time: 52.348 ms
File size: 262144 KB, Read time: 103.848 ms
File size: 524288 KB, Read time: 206.188 ms
File size: 1048576 KB, Read time: 408.917 ms
"""

def parse_data(dataset):
    sizes = []
    latencies = []
    for line in dataset.strip().split('\n'):
        parts = line.split(',')
        size_kb = int(parts[0].split()[2])
        latency_ms = float(parts[1].split()[2])
        sizes.append(np.log2(size_kb))
        latencies.append(latency_ms)
    return sizes, latencies

sizes1, latencies1 = parse_data(data)
sizes2, latencies2 = parse_data(data2)

# draw figure
# Split the data for two subplots
split_index = 15  # Choose an appropriate index to split the data
sizes1_left, sizes1_right = sizes1[:split_index], sizes1[split_index:]
sizes2_left, sizes2_right = sizes2[:split_index], sizes2[split_index:]
latencies1_left, latencies1_right = latencies1[:split_index], latencies1[split_index:]
latencies2_left, latencies2_right = latencies2[:split_index], latencies2[split_index:]

# Plotting
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 4))

# Left subplot for smaller sizes
ax1.plot(sizes1_left, latencies1_left, marker='o', label='First Access')
ax1.plot(sizes2_left, latencies2_left, marker='x', label='Full Cached Access')
ax1.set_xlabel('Log2 (File Access Size (KiB))', fontsize=14)
ax1.set_ylabel('Average Latency (ms)', fontsize=14)
ax1.set_title('(a) Smaller File Sizes', fontsize=14)
ax1.legend()

# Right subplot for larger sizes
ax2.plot(sizes1_right, latencies1_right, marker='o', label='First Access')
ax2.plot(sizes2_right, latencies2_right, marker='x', label='Full Cached Access')
ax2.set_xlabel('Log2 (File Access Size (KiB))', fontsize=14)
#ax2.set_ylabel('Average Latency (ms)')
ax2.set_title('(b) Larger File Sizes', fontsize=14)
ax2.legend()

#plt.ylim([0, 140])
plt.tight_layout()
plt.savefig('filecache.pdf',dpi=300)
plt.show()


