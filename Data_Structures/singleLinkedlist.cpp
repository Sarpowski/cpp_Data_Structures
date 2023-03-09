
#include <iostream>
#include <string>

template <class KeyT>
class DictionaryList
{
public:
    DictionaryList() :
        head_(nullptr)
    {}

    ~DictionaryList();


    bool is_itExist(const KeyT& key) const;
    bool insert(const KeyT& key);
    bool remove(const KeyT& key);
    bool search(const KeyT& key);

    void merge(DictionaryList<KeyT>& other);
    void intersect(const DictionaryList<KeyT>& list1, const DictionaryList<KeyT>& list2);

    
    void subtract(const DictionaryList<KeyT>& other); 

    friend std::ostream& operator<<(std::ostream& stream, const DictionaryList& list)
    {
        Node* temp = list.head_;
        if (temp == nullptr)
        {
            std::cout << "list is empty " << std::endl;

        }
        while (temp)
        {
            stream << temp->key << "  ";
            temp = temp->next;
        }
        return stream;
    }






private:
    struct Node
    {
        KeyT key;
        Node* next;

        Node(const KeyT& k, Node* n = nullptr) :
            key(k),
            next(n)
        {}
    };

    Node* head_;

    DictionaryList(const DictionaryList&) = delete;
    DictionaryList& operator=(const DictionaryList&) = delete;
};
template <class KeyT>
bool DictionaryList<KeyT>::is_itExist(const KeyT& key) const
{
    Node* curr = head_;
    while (curr) {
        if (curr->key == key) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}


template <class KeyT>
bool DictionaryList<KeyT>::remove(const KeyT& key)
{
    Node* prev = nullptr;
    Node* curr = head_;
   
    
        while (curr && curr->key != key)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr)
        {
            if (prev)
            {
                prev->next = curr->next;
            }
            else
            {
                head_ = curr->next;
            }
            delete curr;
            return true;
        }

        return false;
    
   
    

}



template <class KeyT>
bool DictionaryList<KeyT>::search(const KeyT& key)
{
    Node* curr = head_;
    while (curr && curr->key != key)
    {
        curr = curr->next;
    }

    if (curr)
    {
        std::cout << key << "in the list \n";
        return true;
    }
    else {
        std::cout << "key isnt in the list \n";
        return false;
    }
}


template <class KeyT>
void DictionaryList<KeyT>::merge(DictionaryList& other)
{
    Node* current_other = other.head_;
    while (current_other)
    {
        if (!is_itExist(current_other->key))
        {
            insert(current_other->key);
        }
        current_other = current_other->next;
    }
    if (other.head_ != nullptr)
    {
        std::cout << "Merge " << std::endl;

    }
    else
    {
        std::cout << "list is empty "<<std::endl;
    }
    other.head_ = nullptr;
}






template <class KeyT>
bool DictionaryList<KeyT>::insert(const KeyT& key)
{
    bool checkBeforeADD = is_itExist(key);
    if (checkBeforeADD == true)
    {
        std::cout << "you cant add the same element to list it need to be unique" << std::endl;
        return false;
    }

    Node* new_node = new Node(key);

    if (head_ == nullptr) {
        head_ = new_node;
        return true;
    }

    // !!! inserting at the beginning of the list
    if (key < head_->key) {
        new_node->next = head_;
        head_ = new_node;
        return true;
    }

    // find  before the insert point
    Node* prev = head_;
    while (prev->next != nullptr && prev->next->key < key) {
        prev = prev->next;
    }

    // insert  new node
    new_node->next = prev->next;
    prev->next = new_node;
    return true;
}



template <class KeyT>
DictionaryList<KeyT>::~DictionaryList()
{
    while (head_)
    {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
    head_ = nullptr;
}



template <class KeyT>
void DictionaryList<KeyT>::subtract(const DictionaryList<KeyT>& other)
{
    Node* curr = head_;
    Node* prev = nullptr;

    while (curr)
    {
        if (other.is_itExist(curr->key))
        {
            Node* temp = curr;
            curr = curr->next;

            if (prev)
            {
                prev->next = curr;
            }
            else
            {
                head_ = curr;
            }

            delete temp;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

template <class KeyT>
void DictionaryList<KeyT>::intersect(const DictionaryList<KeyT>& list1, const DictionaryList<KeyT>& list2)
{
    DictionaryList<KeyT> intersection;

    typename DictionaryList<KeyT>::Node* curr1 = list1.head_;
    while (curr1)
    {
        if (list2.is_itExist(curr1->key))
        {
            intersection.insert(curr1->key);
        }
        curr1 = curr1->next;
    }

    std::cout << intersection;
}

void dictionaryTest();
void operationTest();


int main()
{
   
   // dictionaryTest(); //worked 
    operationTest(); //testing right now
}
void operationTest()
{
    std::cout<<"test for operations \n ";
    // Объединение списков
    // void merge(DictionaryList& dict2)
    DictionaryList<std::string> dictStr;
    dictStr.insert("789");
    dictStr.insert("345");
    dictStr.insert("567");
    dictStr.insert("321");
    dictStr.insert("82");

    std::cout << "Before merge:\n";
    std::cout << dictStr << '\n';

    DictionaryList<std::string> dictStr2;
    dictStr2.insert("81");
    dictStr2.insert("123");
    dictStr2.insert("456");
    dictStr2.insert("9");
    dictStr2.insert("987");
    // повторяющийся элемент
    dictStr2.insert("567");

    std::cout << dictStr2 << '\n';

    dictStr.merge(dictStr2);

    std::cout << "After merge:\n";
    std::cout << dictStr << '\n';
    std::cout << dictStr2 << '\n';

    // объединение с пустым списком ,merging with empty lists
    std::cout << "Merge with empty list:\n";
    dictStr.merge(dictStr2);
    dictStr2.merge(dictStr);
    dictStr.merge(dictStr2);
    std::cout << dictStr << '\n';
    std::cout << dictStr2 << '\n';

    // Вычитание списков
    // void subtract(const DictionaryList& dict2)
    dictStr2.insert("81");
    dictStr2.insert("123");
    dictStr2.insert("456");
    dictStr2.insert("9");
    dictStr2.insert("987");
    dictStr2.insert("888");
    dictStr2.insert("777");
    dictStr2.insert("444");

    std::cout << "Before subtraction:\n";
    std::cout << dictStr << '\n';
    std::cout << dictStr2 << '\n';

    dictStr.subtract(dictStr2);

    std::cout << "After subtraction:\n";
    std::cout << dictStr << '\n';
    std::cout << dictStr2 << '\n';

    // вычитание пустого списка
    dictStr.subtract(DictionaryList<std::string>());

    std::cout << "Subtract empty list:\n";
    std::cout << dictStr << '\n';

    // вычитание из пустого списка
    DictionaryList<std::string>().subtract(dictStr);

    // Пересечение списков
    // DictionaryList intersect(const DictionaryList& dict1, const DictionaryList& dict2)

    DictionaryList<std::string> dictStr3;
    dictStr3.insert("789");
    dictStr3.insert("345");
    dictStr3.insert("567");
    // неповторяющиеся элементы
    dictStr3.insert("589");
    dictStr3.insert("467");
    std::cout<<"---test 1--- \n";
    DictionaryList<std::string> dictStr4 ;
     dictStr4.intersect(dictStr, dictStr3);

    std::cout << "After intersection:\n";
    std::cout << dictStr << '\n';
    std::cout << dictStr3 << '\n';
    std::cout << dictStr4 << '\n';

    // пересечение пустых списков
    std::cout<<"----test 2---- \n";
    dictStr4.intersect(DictionaryList<std::string>(), DictionaryList<std::string>());
    std::cout << "Intersection of empty lists:\n";
    std::cout << dictStr4 << '\n';
}

void dictionaryTest()
{
    // Создание списка
    // bool insert(const KeyT& key)
    DictionaryList<int> dictInt;
    dictInt.insert(9);
    dictInt.insert(2);
    dictInt.insert(5);
    dictInt.insert(7);
    // вставка нового элемента
    if (dictInt.insert(1))
    {
        std::cout << "inserted\n";
    }
    // вставка существующего элемента
    if (!dictInt.insert(5))
    {
        std::cout << "already exists\n";
    }

    std::cout << dictInt << '\n';

    // Поиск элемента
    // bool search(const KeyT& key)
    // существующие элементы
    if (dictInt.search(1))
    {
        std::cout << "found\n";
    }
    if (dictInt.search(5))
    {
        std::cout << "found\n";
    }
    if (dictInt.search(9))
    {
        std::cout << "found\n";
    }
    // несуществующие элементы
    if (!dictInt.search(-8))
    {
        std::cout << "not found\n";
    }
    if (!dictInt.search(4))
    {
        std::cout << "not found\n";
    }
    if (!dictInt.search(15))
    {
        std::cout << "not found\n";
    }

    // Удаление элементов
    // bool remove(const KeyT& key)
    // существующие элементы
    if (dictInt.remove(5))
    {
        std::cout << "deleted\n";
    }
    if (dictInt.remove(1))
    {
        std::cout << "deleted\n";
    }
    if (dictInt.remove(9))
    {
        std::cout << "deleted\n";
    }

    std::cout << dictInt << '\n';

    // несуществующий элемент
    if (!dictInt.remove(15))
    {
        std::cout << "not found\n";
    }
	
	// удаление оставшихся элементов
	if (dictInt.remove(2))
    {
        std::cout << "deleted\n";
    }
	if (dictInt.remove(7))
    {
        std::cout << "deleted\n";
    }
	
	std::cout << dictInt << '\n';
}