import random


def bucket_sort(array):
    result = []
    buckets = [[] for _ in array]

    for elem in array:
        buckets[int(len(array) * elem)].append(elem)
    for bucket in buckets:
        result.extend(sorted(bucket))  # insertion sort

    return result


array = [float("%.3f" % random.uniform(0, 1)) for _ in range(10)]
print(array)
print(bucket_sort(array))

# [0.162, 0.577, 0.956, 0.625, 0.182, 0.5, 0.965, 0.567, 0.371, 0.388]
# [0.162, 0.182, 0.371, 0.388, 0.5, 0.567, 0.577, 0.625, 0.956, 0.965]
