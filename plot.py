import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Load data from a .txt file
data = np.loadtxt('latencies90_100ms.txt')

# data /= 2496913526 intial correction factor 

# Calculate statistics
min_value = np.min(data)
max_value = np.max(data)
mean = np.mean(data)
median = np.median(data)
std_dev = np.std(data)

# printing values
print(f"min_value: {min_value}")
print(f"max_value: {max_value}")
print(f"mean: {mean}")
print(f"median: {median}")
print(f"std_dev: {std_dev}")



# Plot the histogram for continuos value 
plt.hist(data, bins=1000, edgecolor='black')

# Add title and labels
plt.title('Histogram for 100ms and 10000 iterations')
plt.xlabel('Time(seconds)')
plt.ylabel('Frequency')
plt.show()

# all for no priority 
# counts for  1ms and 10000 iterations and time is in microseconds
# Number of values between 0 and 5: 13
# Number of values between 5 and 20: 1938
# Number of values between 20 and 35: 30
# Number of values between 35 and 50: 635
# Number of values between 50 and 70: 178
# Number of values between 70 and 120: 7158
# Number of values between 120 and infinity : 48

# counts for 10ms and 10000 iterations and time is in microseconds
# Number of values between 0 and 10: 6
# Number of values between 10 and 20: 1511
# Number of values between 20 and 30: 161
# Number of values between 30 and 45: 36
# Number of values between 45 and 55: 261
# Number of values between 55 and 80: 132
# Number of values between 80 and 125: 7844
# Number of values between 125 and infinity : 49


# counts for 100ms and 10000 iterations and time is in microseconds
# Number of values between 0 and 20: 1685
# Number of values between 20 and 30: 354
# Number of values between 30 and 40: 45
# Number of values between 40 and 60: 531
# Number of values between 60 and 120: 7295
# Number of values between 120 and infinity: 90


