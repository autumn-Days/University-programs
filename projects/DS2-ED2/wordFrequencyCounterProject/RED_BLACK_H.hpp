#ifndef RED_BLACK_H
#define RED_BLACK_H

#define RED 0
#define BLACK 1

#include <iostream>
#include <unicode/unistr.h>
#include <stdexcept>
using namespace std;

template <typename keyType, typename valueType>
class NodeRedBlack
{
public:
    keyType key;
    valueType value;
    int color;
    NodeRedBlack<keyType,valueType>* left;
    NodeRedBlack<keyType,valueType>* right;
    NodeRedBlack<keyType,valueType>* parent;

    NodeRedBlack(keyType key, valueType value, int color, 
                NodeRedBlack<keyType,valueType>* left = nullptr,
                NodeRedBlack<keyType,valueType>* right = nullptr,
                NodeRedBlack<keyType,valueType>* parent = nullptr)
    {
        this->key = key;
        this->value = value;
        this->color = color;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }

    int getColor()
    {
        return _getColor(this);
    }

    void setColor(int color)
    {
        this->color = color;
    }
private:
    int _getColor(NodeRedBlack<keyType,valueType>* node)
    {
        if (node == nullptr)
            return BLACK;
        return node->color;
    }
};

template <typename keyType, typename valueType>
class RedBlackTree
{
public:
    NodeRedBlack<keyType,valueType>* root;
    int counter;
public:
    RedBlackTree()
    {
        this->root = nullptr;
        this->counter = 0;
    }

    ~RedBlackTree()
    {
        _clear(this->root);
    }

    void clear()
    {
        _clear(this->root);
    }

    int size()
    {
        return _size(this->root);
    }

    bool contains(keyType key)
    {
        return _contains(this->root, key);
    }

    valueType get(keyType key)
    {
        NodeRedBlack<keyType,valueType>* nodeGot = _search(this->root, key);
        if (nodeGot == nullptr)
            throw std::invalid_argument("GET ERROR! No such a key!\n");
        return nodeGot->value;
    }

    void modify(keyType key, valueType newValue)
    {
        _modify(this->root, key, newValue);
    }

    void add(keyType key, valueType value)
    {
        NodeRedBlack<keyType,valueType>* newNode = new NodeRedBlack(key, value, RED);
        if (this->root == nullptr)
        {
            newNode->color = BLACK;
            this->root = newNode;
            return;
        }
        else
        {
            this->root = _add(this->root,newNode);
            if (newNode->parent->parent)
            {
                _fixAdd(newNode);
            }   
        }
    }

    void remove(keyType key)
    {
        _remove(this->root,key);
    }

    int getCounter()
    {
        return this->counter;
    }

    void inOrderUni()
    {
        _inOrderUni(this->root);
    }

    void inOrder()
    {   
        _inOrder(this->root);
    }


private:

    void _modify(NodeRedBlack<keyType,valueType>*& node,keyType key, valueType newValue)
    {
        NodeRedBlack<keyType,valueType>*& nodeGot = _search(node, key);
        if (nodeGot == nullptr)
            throw std::invalid_argument("MODIFY ERROR! No such a key!\n");
        nodeGot->value = newValue;
    }

    void _fixAdd(NodeRedBlack<keyType, valueType>*& newNode)
    {
        /*Quando o pai do nódulo que acaba de ser inserido é negro, é garantido que não há mais
         quebras na quarta propriedade da rubro-negra e, se ao subir na árvore, "newNode" se torna
         a raiz, também é verificado que não há mais quebras da 4° propriedade, pois a raiz é negra*/
        while(newNode->parent->getColor() != BLACK && newNode != this->root)
        {
            //1° CASO SIMÉTRICO: PAI ESQUERDO
            if (newNode->parent == newNode->parent->parent->left)
            {
                //1° caso: O pai e o tio são vermelhos
                if (_getBrotherColor(newNode->parent) == RED)
                {
                    //pinto o pai e o tio de negros
                    newNode->parent->setColor(BLACK); 
                    newNode->parent->parent->right->setColor(BLACK);
                    //pinta o avô de vermelho
                    newNode->parent->parent->setColor(RED);
                    //subo na árvore para garantir que as cores se matenham
                    newNode = newNode->parent->parent;
                }
                else
                {
                    //2° caso: Pai vermelho, tio preto e eu sou o filho direito
                    if (newNode == newNode->parent->right)
                    {
                        newNode = newNode->parent;
                        _leftRotation(newNode);
                    }            
                    //3° caso: Pai vermelho, tio preto e eu sou o filho esquerdo
                    newNode->parent->setColor(BLACK);
                    newNode->parent->parent->setColor(RED);
                    //Rotação a direita no avó
                    _rightRotation(newNode->parent->parent);
                }
            }
            else
            {
                //1° caso: O pai e o tio são vermelhos
                if (_getBrotherColor(newNode->parent) == RED)
                {
                    //pinto o pai e o tio de negros
                    newNode->parent->setColor(BLACK);
                    newNode->parent->parent->left->setColor(BLACK);
                    //pinta o avô de vermelho~
                    newNode->parent->parent->setColor(RED);
                    //subo na árvore para garantir que as cores se matenham
                    newNode = newNode->parent->parent;
                }
                else
                {
                    //2° caso: Pai vermelho, tio preto e eu sou o filho direito
                    if (newNode == newNode->parent->left)
                    {
                        newNode = newNode->parent;
                        _rightRotation(newNode);
                    }            
                    //3° caso: Pai vermelho, tio preto e eu sou o filho esquerdo
                    newNode->parent->setColor(BLACK);
                    newNode->parent->parent->setColor(RED); 
                    //Rotação a direita no avó
                    _leftRotation(newNode->parent->parent);
                }
            }
        }
        //4° caso: Só pintar a raiz de preto
        this->root->setColor(BLACK);
    }


    void _remove(NodeRedBlack<keyType,valueType>*& node, keyType key)
    {
        if (node == nullptr)
            throw std::invalid_argument("REMOVE ERROR! NO SUCH A KEY!");
        else if (key > node->key)
            _remove(node->right, key);
        else if (key < node->key)
            _remove(node->left, key);
        else
        {
            bool isBlack = false;
            //O nódulo é uma folha
            if (node->left == nullptr && node->right == nullptr)
            {
                isBlack = node->getColor();
                NodeRedBlack<keyType,valueType>*& myParent = node->parent;
                if (node == myParent->left)
                    myParent->left = nullptr;
                else if (node == myParent->right)
                    myParent->right = nullptr;
                delete node;
            }
            //O nódulo tem no máximo um filho
            /*
            Antes de deletar o nódulo, é necessário salvar uma referência
            para o seu pai e para seu único filho. Após a deleção do nódu-
            lo em questão, basta fazer com que o pai do nódulo deletado
            aponte para o filho orfão e o filho orfão aponte para o pai
            do nódulo deletado (seu avô)
            */
            else if (node->left != nullptr || node->right != nullptr)
            {
                isBlack = node->getColor();
                bool isRightChild = false;

                if (node == node->parent->right)
                    isRightChild = true;
                
                NodeRedBlack<keyType,valueType>*& myParent = node->parent;
                NodeRedBlack<keyType,valueType>*& myChild = (node->left != nullptr) ? node->left : node->right;     

                delete node;

                if (isRightChild)
                    myParent->right = myChild;
                else
                    myParent->left = myChild;
                myChild->parent = myParent;
                
            }
            //O nódulo tem 2 filhos
            else
            {
                isBlack = node->getColor();
                NodeRedBlack<keyType,valueType>*& mySuccessor = _minimumReference(node->right);
                node->key = mySuccessor->key;
                node->value = mySuccessor->value;
                _remove(mySuccessor, key);
            }
            /*Se um nó negro foir removido, com certeza a 5° propriedade foi quebrada*/
            if(isBlack)
                _fixRemove(node);
        }
    }


    void _fixRemove(NodeRedBlack<keyType,valueType>*& node)
    {
        while (node != this->root && node->color == BLACK)
        {
            NodeRedBlack<keyType,valueType>*& myParent = node->parent;
            NodeRedBlack<keyType,valueType>*& rightBrother = myParent->right;
            NodeRedBlack<keyType,valueType>*& leftBrother = myParent->left;
            
            //Caso simétrico 1
            if (node == myParent->left)
            {
                //CASO 1: pai negro, irmão vermelho
                if (myParent->color == BLACK && rightBrother->color == RED)
                {
                    myParent->color = RED;
                    rightBrother->color = BLACK;
                    _leftRotation(myParent);
                }

                //CASO 2: não importa a cor do pai, o problema é jogado para cima
                if (rightBrother->left->color == BLACK && rightBrother->right != nullptr && rightBrother->color == BLACK)
                {
                    rightBrother->color = RED;
                    node = myParent;
                    myParent = myParent->parent;
                }
                //CASO 3 e 4
                else
                {
                    bool wentToThirdCase = false;
                    //Caso 3: pai vermelho, irmão preto e sobrinho esquerdo vermelho
                    if (myParent->color == RED && rightBrother->color == BLACK && rightBrother->left->color == RED)
                    {
                        rightBrother->color = BLACK;
                        rightBrother->left->color = BLACK;
                        _rightRotation(rightBrother); //como isso vamos para o caso 4
                        wentToThirdCase = true;
                    }
                    //Caso 4: pai vermelho, irmão preto e sobrinho direito vermelho
                    if (myParent->color == RED && rightBrother->color == BLACK && rightBrother->right->color == RED)
                    {
                        /*Se eu o caso 3 foi visitado para chegar no caso 4, significa que o rightBrother passa
                        para a direita, o que significa que ele não é mais o irmao direito, portanto é necessário atualizá-lo*/
                        if (wentToThirdCase)
                            rightBrother = myParent->right;
                        int tempColor = myParent->color;
                        myParent->color = rightBrother->color;
                        rightBrother->color = tempColor;
                        _leftRotation(myParent);
                        myParent->parent->right->color = BLACK;
                            
                        if (myParent == this->root)
                            break;
                    }
                }
            }
            //Caso simétrico 2
            else if (node == myParent->right)
            {
                //CASO 1: pai negro, irmão vermelho
                if (myParent->color == BLACK && leftBrother->color == RED)
                {
                    myParent->color = RED;
                    leftBrother->color = BLACK;
                    _leftRotation(myParent);
                }

                //CASO 2: não importa a cor do pai, jogo o problema para cima
                if (leftBrother->left->color == BLACK && leftBrother != nullptr && leftBrother->color == BLACK)
                {
                    leftBrother->color = RED;
                    node = myParent;
                    myParent = myParent->parent;
                }
                //CASO 3 e 4
                else
                {
                    bool wentToThirdCase = false;
                    //Caso 3: pai vermelho, irmão preto e sobrinho esquerdo vermelho
                    if (myParent->color == RED && leftBrother->color == BLACK && leftBrother->left->color == RED)
                    {
                        leftBrother->color = BLACK;
                        leftBrother->left->color = BLACK;
                        _rightRotation(leftBrother); //como isso vamos para o caso 4
                        wentToThirdCase = true;
                    }
                    //Caso 4: pai vermelho, irmão preto e sobrinho direito vermelho
                    if (myParent->color == RED && leftBrother->color == BLACK && leftBrother->right->color == RED)
                    {
                        /*Caso o 3° caso tenha sido visitado antes antes deste, significa que eu rotacionei o leftBrother
                        para a direita, o que significa que ele não é mais o irmão direito, portanto preciso atualizar ele*/
                        if (wentToThirdCase)
                            leftBrother = myParent->right;
                        int tempColor = myParent->color;
                        myParent->color = leftBrother->color;
                        leftBrother->color = tempColor;
                        _leftRotation(myParent);
                        myParent->parent->right->color = BLACK;
                            
                        if (myParent == this->root)
                            break;
                    }
                }
            }
        }
        if (node != nullptr)
            node->color = BLACK;
    }


    NodeRedBlack<keyType,valueType>*& _minimumReference(NodeRedBlack<keyType, valueType>*& node)
    {
        if (node->left == nullptr && node->right == nullptr)
            return node;
        return _minimumReference(node->left);
    }

    /*Este método vai receber o nódulo pai do nódulo que acabou de ser inserido
     e vai obter a sua cor*/
    int _getBrotherColor(NodeRedBlack<keyType, valueType>* node)
    {
        if (node->parent != nullptr)
        {
            if (node == node->parent->left)
            {
                if(node->parent->right != nullptr)
                    return node->parent->right->color;
                /*Se o filho direito for um ponteiro nulo, então ele é preto*/
                return BLACK;
            }
            else if (node == node->parent->right)
            {
                if (node->parent->left != nullptr)
                    return node->parent->left->color;
                return BLACK; //se o node não tiver irmão
            }
        }
        return -1; //se o node não tiver pai, um valor inválido é retornado para servir como flag
    }

    int size(NodeRedBlack<keyType, valueType>* node)
    {
        if ((node->left == nullptr) && (node->right == nullptr))
            return 1;
        return 1 + size(node->left) + size(node->right);
    }

    bool _contains(NodeRedBlack<keyType, valueType>* node, keyType key)
    {
        NodeRedBlack<keyType,valueType>*& node2Look4 = _search(this->root,key);
        if (node2Look4 != nullptr)
            return true;
        return false;
    }

    /*
    Este método é chamado pelo "modify", "contains" e "get". Portanto, o contador é incrementado
    Ao lê-lo.
    */
    NodeRedBlack<keyType,valueType>*& _search(NodeRedBlack<keyType, valueType>*& node, keyType key)
    {
        this->counter++;
        if (node == nullptr || node->key == key)
        {
            return node;
        }
        else if (key > node->key)
        {
            return _search(node->right, key);
        }
        return _search(node->left, key);      
    }

    NodeRedBlack<keyType, valueType>* _add(NodeRedBlack<keyType, valueType>*root,NodeRedBlack<keyType, valueType>* newNode)
    {
        this->counter ++;
        if (newNode->key > root->key)
        {
            /*
            A médida que é necessário manter a referência para os 
            pais, antes de avançar reursivamente para baixo da ár-
            vore, é necessário verificar se o filho do nódulo que
            se quer inserir é ou não nulo, caso seja nulo, isso
            significa que o novo nódulo achou o seu pai. Desta forma,
            antes que a inserção ocorra de fato, o ponteiro "parent"
            de "root" aponta para "root" para que depois, root
            o "aceite como filho". A mesma lógica é empregada para
            a o caso em que "newNode" é inserido à esquerda. 
            */
            if (root->right == nullptr)
            {
                newNode->parent = root;
                root->right = newNode;
            }
            else
                _add(root->right, newNode);
        }
        else if (newNode->key < root->key)
        {
            if (root->left == nullptr)
            {
                newNode->parent = root;
                root->left = newNode;
            }
            else
                _add(root->left, newNode);
        }
        return root;
    }

    void _rightRotation(NodeRedBlack<keyType, valueType>* node2rotate)
    {
        //Condição que evita segmentation fault
        if (node2rotate == nullptr || node2rotate->left == nullptr)
            return;
        else
        {
            /*É necessário fazer uma copia do nódulo esquerdo, pois a referência
            para ele será perdida posteriormente*/
            NodeRedBlack<keyType,valueType>* copyLeft = node2rotate->left;
            node2rotate->left = copyLeft->right;
            /*A cada passa da rotação é necessário verificar se o nódulo que se está buscando
            é ou não nulo. Prosseguir com cautela é necessário para evitar erros de segmentação*/
            if (copyLeft->right != nullptr)
                copyLeft->right->parent = node2rotate;
            copyLeft->parent = node2rotate->parent;
            if (node2rotate->parent == nullptr)
                this->root = copyLeft;
            //Begin:o pai de "node2rotate" aponta para "copyLeft"
            else if (node2rotate == node2rotate->parent->left)
                node2rotate->parent->left = copyLeft;
            else
                node2rotate->parent->right = copyLeft;
            //End
            copyLeft->right = node2rotate;
            node2rotate->parent = copyLeft;
        }
    }

    /*
    Os mesmos comentários aplicados a rotação a direita também se aplicam a esquerda,
    pois eles são simétricos
    */
    void _leftRotation(NodeRedBlack<keyType, valueType>* node2rotate)
    {
        if (node2rotate == nullptr || node2rotate->right == nullptr)
            return;
        else
        {
            NodeRedBlack<keyType,valueType>* copyRight = node2rotate->right;
            node2rotate->right = copyRight->left;
            if (copyRight->left != nullptr) 
                copyRight->left->parent = node2rotate; 
            copyRight->parent = node2rotate->parent; 
            if(node2rotate->parent == nullptr) 
                this->root = copyRight;
            //begin: o pai de "node2rotate" aponta para "copyRight"
            else if (node2rotate == node2rotate->parent->left) 
                node2rotate->parent->left = copyRight;
            else
                node2rotate->parent->right = copyRight;
            //End    
            copyRight->left = node2rotate;
            node2rotate->parent = copyRight;
        }
    }

    //Prints the inOrder of the RB-tree for UnicodeStrings
    void _inOrderUni(NodeRedBlack<icu::UnicodeString, valueType>* node)
    {
        if (node != nullptr)
        {
            _inOrderUni(node->left);

            //Convert the UnicodeString key to a UTF-8 string
            string convertedKey;
            node->key.toUTF8String(convertedKey);

            std::cout << convertedKey << ":" << node->value << std::endl;

            _inOrderUni(node->right);
        }
    }
    //prints the the inOrder of the types defined in the std
    void _inOrder(NodeRedBlack<keyType, valueType>* node)
    {
        if (node != nullptr)
        {
            _inOrder(node->left);

            // Convert the UnicodeString key to a UTF-8 string
            std::cout << node->key << ":" << node->value << std::endl;

            _inOrder(node->right);
        }
    }

};

#endif