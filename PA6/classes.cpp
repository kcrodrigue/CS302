using namespace std;
struct Node
{
    int data;
    Node* left_child;
    Node* right_child;
    Node(int input);
};

class BST
{
public:
    BST(); //
    ~BST(); //
    bool is_empty(); //
    void remove(int); //
    bool contains(int); //
    void add(int); //
    int get_height(); //
    void inorder_traversal(); //
    void preorder_traversal(); //
    void postorder_traversal(); //
private:
    void private_preorder_traversal(Node*); //
    void private_postorder_traversal(Node*); //
    int get_height_private(Node*);
    Node* destroy_tree(Node*); //
    Node* search(int, Node*); //
    bool private_contains(int, Node*); //
    Node* private_remove(Node*); //
    void private_inorder(Node*); //
    void private_add(int, Node*&); //
    Node* root;
};

Node::Node(int input)
{
    data = input;
    left_child = NULL;
    right_child = NULL;
}

BST::BST()
{
    root = NULL;
}

bool BST::is_empty()
{
    if(root == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BST::add(int data)
{
    private_add(data, root);
}

void BST::private_add(int input, Node *&here)
{
    if(here == NULL)
    {
        here = new Node(input);
        return;
    }

    else if(input > here->data)
    {
        private_add(input, here->right_child);
    }

    else if(input < here->data)
    {
        private_add(input, here->left_child);
    }
}

void BST::inorder_traversal()
{
    private_inorder(root);
}

void BST::private_inorder(Node* here)
{
    if(here != NULL)
    {
        private_inorder(here->left_child);
        cout << here->data << " ";
        private_inorder(here->right_child);
    }

}

Node* BST::search(int input, Node* here)
{
    if(here != NULL)
    {
        if(input == here->data)
        {
            return here;
        }
        if(input < here->data)
        {
            return search(input, here->left_child);
        }
        if(input > here->data)
        {
            return search(input, here->right_child);
        }
    }
    return NULL;
}

void BST::remove(int input)
{
    if(contains(input))
    {
        private_remove(search(input, root));
    }
}

Node* BST::private_remove(Node *here)
{

    if(here == NULL)
    {
        return here;
    }
    // no children
    else if(here->right_child == NULL && here->left_child == NULL)
    {
        delete here;
    }
    // just left child
    else if(here->right_child == NULL)
    {
        Node* temp;
        temp = here;
        here = here->left_child;
        delete temp;
    }

    // just right child
    else if(here->left_child == NULL)
    {
        Node* temp;
        temp = here;
        here = here->right_child;
        delete temp;
    }

    // both children
    else
    {
        Node* temp;
        temp = here->right_child;

        while (temp->left_child != NULL)
        {
            temp = temp->left_child;
        }

        here->data = temp->data;

        delete temp;
    }

    return here;

}

bool BST::contains(int input)
{
    if(!is_empty())
    {
        return private_contains(input, root);
    }
    else
    {
        return false;
    }
}

bool BST::private_contains(int input, Node* here)
{
    if(here == NULL)
    {
        return false;
    }

    if(input == here->data && here != root)
    {
        return true;
    }

    else if(input > here->data)
    {
        return private_contains(input, here->right_child);
    }

    else if(input < here->data)
    {
        return private_contains(input, here->left_child);
    }

    return false;
}

BST::~BST()
{
    //root = destroy_tree(root);
}

Node* BST::destroy_tree(Node* here)
{
    if(here == NULL)
    {
        return NULL;
    }
    //else
    {
        destroy_tree(here->left_child);
        destroy_tree(here->right_child);
        delete here;
    }
    return NULL;
}

int BST::get_height()
{
    return get_height_private(root);
}

int BST::get_height_private(Node* here)
{
    if(here == NULL)
    {
        return 0;
    }
    else
    {
        return(1 + max(get_height_private(here->left_child), get_height_private(here->right_child)));
    }
}

void BST::preorder_traversal()
{
    private_preorder_traversal(root);
}

void BST::private_preorder_traversal(Node* here)
{
    if(here != NULL)
    {
        cout << here->data << " ";
        private_preorder_traversal(here->left_child);
        private_preorder_traversal(here->right_child);
    }
}

void BST::postorder_traversal()
{
    private_postorder_traversal(root);
}

void BST::private_postorder_traversal(Node* here)
{
    if(here != NULL)
    {
        private_postorder_traversal(here->left_child);
        private_postorder_traversal(here->right_child);
        cout << here->data << " ";
    }
}
