import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Load data from a .txt file
data = np.loadtxt('latencies90_100ms.txt')

# Calculate statistics
min_value = np.min(data)
max_value = np.max(data)
mean = np.mean(data)
median = np.median(data)
std_dev = np.std(data)

# Printing values
print(f"min_value: {min_value}")
print(f"max_value: {max_value}")
print(f"mean: {mean}")
print(f"median: {median}")
print(f"std_dev: {std_dev}")

# Manually define the data for the second histogram
# Define the bin edges for the second histogram
bin_edges1 = [0.0, 0.000020, 0.000035, 0.000060, 0.000075, 0.000110, 0.000140, 0.000180]

# Create subplots
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 12))

# Plot the histogram for continuous values on the first subplot
ax1.hist(data, bins=1000, edgecolor='red')
ax1.set_title('Histogram for 100ms and 10000 iterations')
ax1.set_xlabel('Time(seconds)')
ax1.set_ylabel('Frequency')

# Plot the histogram for discrete values on the second subplot
hist1, bins1 = np.histogram(data, bins=bin_edges1)
ax2.hist(data, bins=bin_edges1, edgecolor='black', alpha=0.7)
ax2.set_xlabel('Time(seconds)')
ax2.set_ylabel('Frequency')
ax2.set_title('Histogram with Discrete Ranges')

# Show the bin edges and counts
for i in range(len(hist1)):
    ax2.text((bins1[i] + bins1[i+1]) / 2, hist1[i], f'{hist1[i]}\n({bins1[i]}, {bins1[i+1]})', 
             ha='center', va='bottom', fontsize=10, color='green')
# Grid and layout adjustments
ax1.grid(True)
ax2.grid(True)
plt.tight_layout()

# Show the plot
plt.show()
