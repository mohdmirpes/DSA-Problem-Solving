class node:
    def __init__(self, data):
        self.data = data
        self.next = None
n=int(input("Enter the number of nodes: "))
for i in range(n):
    data = int(input("Enter the data: "))
    if i == 0:
        head = node(data)
        temp = head
    else:
        temp.next = node(data)
        temp = temp.next
print("The linked list before is : ", end="")
for j in range(n):
    if j == 0:
        print(head.data, end=" ")
        temp = head.next
    else:
        print(temp.data, end=" ")
        temp = temp.next
prev= None
temp=head.next
while temp is not None:
    head.next = prev
    prev = head
    head = temp
    temp = temp.next
head.next = prev
print("\nThe linked list after is : ", end="")
for k in range(n):
    if k == 0:
        print(head.data, end=" ")
        temp = head.next
    else:
        print(temp.data, end=" ")
        temp = temp.next