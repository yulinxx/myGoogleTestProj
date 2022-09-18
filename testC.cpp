// https://blog.csdn.net/weixin_33692284/article/details/93552030

#include <stddef.h>

//////////////////////////////////////////////////////////////////
// Queue 是一个单向链表的简单实现.
//
// The element 必须支持拷贝构造.
template <typename E> // E is the element type
class Queue;

//////////////////////////////////////////////////////////////////
// QueueNode 是组成 Queue的一个节点
// type E and a pointer to the next node.
template <typename E> // E is the element type
class QueueNode
{
    friend class Queue<E>;

public:
    // 获取本节点的 element.
    const E &element() const { return m_element; }

    // 获取下一个节点.
    QueueNode* next() { return m_pNext; }
    const QueueNode* next() const { return m_pNext; }

private:
    // 用给定的element创建一个节点，next pointer 被设定为空
    QueueNode(const E &an_element) : m_element(an_element), m_pNext(NULL) {}

    // We disable the default assignment operator and copy c'tor.
    const QueueNode &operator=(const QueueNode &);
    QueueNode(const QueueNode &);

    E m_element;
    QueueNode* m_pNext;
};

//////////////////////////////////////////////////////////////////
template <typename E> // E is the element type.
class Queue
{
public:
    // 创建一个空队列.
    Queue() : head_(NULL), last_(NULL), size_(0) {}

    // 析构
    ~Queue() { Clear(); }

    // 清理队列.
    void Clear()
    {
        if (size_ > 0)
        {
            // 1. 删除所有节点.
            QueueNode<E>* node = head_;
            QueueNode<E>* next = node->next();
            for (;;)
            {
                delete node;
                node = next;
                if (node == NULL)
                    break;

                next = node->next();
            }

            // 2. Resets the member variables.
            head_ = last_ = NULL;
            size_ = 0;
        }
    }

    // 获取元素数量.
    size_t Size() const { return size_; }

    // 获取队列第一个元素，当队列为空时返回null.
    QueueNode<E> *Head() { return head_; }
    const QueueNode<E> *Head() const { return head_; }

    // 获取队列最后一个元素，当队列为空时返回null.
    QueueNode<E> *Last() { return last_; }
    const QueueNode<E> *Last() const { return last_; }

    // 在队列的尾部加入一个元素，用element的构造函数创建一个element并存贮在队列的尾部
    void Enqueue(const E &element)
    {
        QueueNode<E> *new_node = new QueueNode<E>(element);

        if (size_ == 0)
        {
            head_ = last_ = new_node;
            size_ = 1;
        }
        else
        {
            last_->m_pNext = new_node;
            last_ = new_node;
            size_++;
        }
    }

    // 从头部移除一个元素，并将这个元素返加，队列为空时返Null.
    E *Dequeue()
    {
        if (size_ == 0)
            return NULL;

        const QueueNode<E> *const old_head = head_;
        head_ = head_->m_pNext;
        size_--;

        if (size_ == 0)
            last_ = NULL;

        E *element = new E(old_head->element());
        delete old_head;

        return element;
    }

    // 在队列的每一个元素上应用function,并返回新队列。原队列不受影响
    template <typename F>
    Queue *Map(F function) const
    {
        Queue *new_queue = new Queue();
        for (const QueueNode<E> *node = head_; node != NULL; node = node->m_pNext)
            new_queue->Enqueue(function(node->element()));

        return new_queue;
    }

private:
    QueueNode<E> *head_; // 队列头.
    QueueNode<E> *last_; // 队列尾.
    size_t size_;        // 队列中元素的数量.

    // 禁止队列拷贝及赋值.
    Queue(const Queue &);
    const Queue &operator=(const Queue &);
};

//////////////////////////////////////////////////////////////////
#include "gtest/gtest.h"

class QueueTest : public testing::Test
{
protected: // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // 虚函数SetUp将在所有测试用例之前调用，当有变量需要初始化时，应当定义这个函数
    virtual void SetUp()
    {
        m_q1.Enqueue(1);
        m_q2.Enqueue(2);
        m_q2.Enqueue(3);
    }

    //虚函数 TearDown()将在所有测试用例运行后调用，这个函数用于清理类中的资源，没有资源需要清理时要以不定义
    // virtual void TearDown() {
    // }

    // 用于测试的函数.
    static int Double(int n)
    {
        return 2 * n;
    }

    // 用于测试Queue::Map()的函数.
    void MapTester(const Queue<int> *q)
    {
        // 创建一个队列，这个队列是原队列中数值的两倍
        const Queue<int> *const new_q = q->Map(Double);

        // 确认新老队列的元素数量相同
        ASSERT_EQ(q->Size(), new_q->Size());

        // 确认两个队列的关系
        for (const QueueNode<int> *n1 = q->Head(), *n2 = new_q->Head();
             n1 != NULL; n1 = n1->next(), n2 = n2->next())
        {
            EXPECT_EQ(2 * n1->element(), n2->element());
        }

        delete new_q;
    }

    // Declares the variables your tests want to use.
    Queue<int> m_q0;
    Queue<int> m_q1;
    Queue<int> m_q2;
};

//////////////////////////////////////////////////////////////////

// When you have a test fixture, you define a test using TEST_F
// instead of TEST.

// 测试默认构造函数
TEST_F(QueueTest, DefaultConstructor)
{
    // You can access data in the test fixture here.
    EXPECT_EQ(0u, m_q0.Size());
}

//////////////////////////////////////////////////////////////////

// Tests Dequeue().
TEST_F(QueueTest, Dequeue)
{
    int *n = m_q0.Dequeue();
    EXPECT_TRUE(n == NULL);

    n = m_q1.Dequeue();
    ASSERT_TRUE(n != NULL);
    EXPECT_EQ(1, *n);
    EXPECT_EQ(0u, m_q1.Size());
    delete n;

    n = m_q2.Dequeue();
    ASSERT_TRUE(n != NULL);
    EXPECT_EQ(2, *n);
    EXPECT_EQ(1u, m_q2.Size());
    delete n;
}

//////////////////////////////////////////////////////////////////

// Tests the Queue::Map() function.
TEST_F(QueueTest, Map)
{
    MapTester(&m_q0);
    MapTester(&m_q1);
    MapTester(&m_q2);
}

//////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
