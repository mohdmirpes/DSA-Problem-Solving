def cal_target(lst1, target_sum):
    for j in range(0, len(lst1) - 1):
        for k in range(j + 1, len(lst1)):
            if lst1[j] + lst1[k] == target_sum:
                print(j, k)
    return 0

n = int(input("Enter the number of elements: "))
lst = []
for i in range(n):
    x = int(input("Enter the element to be inserted: "))
    if x not in lst:
        lst.append(x)
    else:
        print("Duplicate value, not added.")

tar = int(input("Enter the target: "))
cal_target(lst, tar)

