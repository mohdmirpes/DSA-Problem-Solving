class node:
    def __init__(self,data):
        self.data = data
        self.left = None
        self.right = None

def inorder_traversal(root):
    if root is None:
        return
    else:
        inorder_traversal(root.left)
        print(root.data, end=' ')
        inorder_traversal(root.right)
        return
    
def inorder_successor(root):
    current = root
    while current.left is not None:
        current = current.left
    return current
    
def insert(root,data):
    if root is None:
        return node(data)
    elif data < root.data:
        root.left=insert(root.left, data)
    else:
        root.right=insert(root.right, data)
    return root

def delete_node(root, value):
    if root is None:
        print("Value not found in the tree.")
        return root
    if value < root.data:
        root.left = delete_node(root.left, value)
    elif value > root.data:
        root.right = delete_node(root.right, value)
    else: 
        if root.left is None and root.right is None:
            root = None
            return root
        elif root.left is None:
            temp = root.right
            root = None
            return temp
        elif root.right is None:
            temp = root.left
            root = None
            return temp
        else:
            temp = inorder_successor(root.right)
            root.data = temp.data
            root.right = delete_node(root.right, temp.data)
    return root

head = None
while True:
    value=input("enter the value or enter q to quit: ")
    if value == 'q':
        break
    else:
        head=insert(head, value)
print("Tree before deletion:")
inorder_traversal(head)
print("\n")

delete_value = input("Enter the value to delete: ")
delete_node(head, delete_value)
print("Tree after deletion:")
inorder_traversal(head)
    
