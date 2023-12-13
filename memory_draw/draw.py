import matplotlib.pyplot as plt
import numpy as np

data = """
buffer: 1 KB, cycles 1732, time 0.000001 s, latency 1.493103 ns
buffer: 2 KB, cycles 3662, time 0.000001 s, latency 1.578448 ns
buffer: 4 KB, cycles 7254, time 0.000003 s, latency 1.563362 ns
buffer: 8 KB, cycles 14556, time 0.000005 s, latency 1.568534 ns
buffer: 16 KB, cycles 29340, time 0.000010 s, latency 1.580819 ns
buffer: 32 KB, cycles 92022, time 0.000032 s, latency 2.479041 ns
buffer: 64 KB, cycles 295084, time 0.000102 s, latency 3.974731 ns
buffer: 128 KB, cycles 629562, time 0.000217 s, latency 4.240046 ns
buffer: 256 KB, cycles 1145362, time 0.000395 s, latency 3.856957 ns
buffer: 512 KB, cycles 3180086, time 0.001097 s, latency 5.354401 ns
buffer: 1024 KB, cycles 14036716, time 0.004840 s, latency 11.817009 ns
buffer: 2048 KB, cycles 58921684, time 0.020318 s, latency 24.802029 ns
buffer: 4096 KB, cycles 106146366, time 0.036602 s, latency 24.340207 ns
buffer: 8192 KB, cycles 239645246, time 0.082636 s, latency 25.218595 ns
buffer: 16384 KB, cycles 1837619304, time 0.633662 s, latency 96.689122 ns
buffer: 32768 KB, cycles 4034712676, time 1.391280 s, latency 106.146258 ns
buffer: 65536 KB, cycles 7747148560, time 2.671431 s, latency 101.906988 ns
buffer: 131072 KB, cycles 17066603888, time 5.885036 s, latency 112.248150 ns
"""

sizes = []
latencies = []
for line in data.strip().split('\n'):
    parts = line.split(',')
    size_part = parts[0]  # "buffer: 1 KB"
    latency_part = parts[3]  # "latency 1.556897 ns"

    size_kb = int(size_part.split()[1])
    latency_ns = float(latency_part.split()[1])

    sizes.append(np.log2(size_kb))
    latencies.append(latency_ns)

annotate_points = {
    '3': 'L1 Cache\n32KiB',
    '8': 'L2 Cache\n1MiB',
    '12': 'L3 Cache\n18MiB/core',
    '16': 'Main Memory'
}

# draw figure
fig = plt.figure(figsize=(5.5, 3.2))
plt.plot(sizes, latencies, marker='o')
plt.xlabel('Log2 (Memory Region Size (KiB))')
plt.ylabel('Average Latency (ns)')
plt.title('Memory Latency')
xtick_labels = [f'{int(size)}' for size in sizes]
plt.xticks(sizes, xtick_labels, rotation=0)
plt.ylim([0, 140])

# add arrows
for xtick, label in zip(xtick_labels, sizes):
    if xtick in annotate_points:
        plt.annotate(annotate_points[xtick],
                     xy=(label, latencies[sizes.index(label)]),
                     xytext=(label - 3, latencies[sizes.index(label)] + 15),
                     arrowprops=dict(facecolor='black', arrowstyle="->", connectionstyle="arc3"),
                     horizontalalignment='left',
                     verticalalignment='bottom')

#plt.grid(True)
fig.tight_layout()
plt.savefig('access_latency.pdf',dpi=300)
plt.show()