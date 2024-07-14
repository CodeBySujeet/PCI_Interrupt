import numpy as np

# Load data from the .txt file
data = np.loadtxt('latencies_10ms.txt')

# Define the range
lower_bound = 0.000125
upper_bound = 1


# Filter the values within the specified range
values_in_range = data[(data >= lower_bound) & (data <= upper_bound)]

# Count the number of values in the range
count_in_range = values_in_range.size

# Print the result
print(f"Number of values between {lower_bound} and {upper_bound}: {count_in_range}")
