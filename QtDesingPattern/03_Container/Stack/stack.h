#include <QDebug>

template <typename T>
class Node
{
public:
    Node(T invalue) : m_Value(invalue), m_Next(nullptr) {}
    ~Node();
    T getValue() const { return m_Value; }
    void setValue(T value) { m_Value = value; }
    Node<T>* getNext() const { return m_Next; }
    void setNext(Node<T> *next) { m_Next = next; }
private:
    T m_Value;
    Node<T> *m_Next;
};

template<typename T>
Node<T>::~Node()
{
    qDebug() << m_Value << " deleted " << endl;
    if (m_Next)
        delete m_Next;
}

template<typename T>
class Stack
{
public:
    Stack() : m_Head(nullptr), m_Count(0) {}
    ~Stack<T>() { delete m_Head; }
    void push(const T& t);
    T pop();
    T top() const;
    int count() const;
private:
    int m_Count;
    Node<T> *m_Head;
};

template<typename T>
void Stack<T>::push(const T& value)
{
    Node<T> *newNode = new Node<T>(value);
    newNode->setNext(m_Head);
    m_Head = newNode;
    ++m_Count;
}

template<typename T>
T Stack<T>::pop()
{
    Node<T> *popped = m_Head;
    if (m_Head != nullptr) {
        m_Head = m_Head->getNext();
        T retval = popped->getValue();
        popped->setNext(nullptr);
        delete  popped;
        --m_Count;
        return retval;
    }
    return 0;
}

template<typename T>
inline T Stack<T>::top() const
{
    return m_Head->getValue();
}

template<typename T>
inline int Stack<T>::count() const
{
    return m_Count;
}
