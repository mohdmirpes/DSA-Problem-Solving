class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def insert(root, data):
    if root is None:
        return Node(data)
    elif data < root.data:
        root.left = insert(root.left, data)
    elif data > root.data:
        root.right = insert(root.right, data)
    return root

def height(root):
    if root is None:
        return -1
    else:
        left_height = height(root.left)
        right_height = height(root.right)
        return 1 + max(left_height, right_height)

head = None
while True:
    n = input("Enter a number (or 'q' to quit): ")
    if n == "q":
        break
    else:
        head = insert(head, int(n))
print("Height of the tree:", height(head))