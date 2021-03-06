#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stddef.h>
#include <initializer_list>
#include <memory>
#include "../Log/graphviz.h"

typedef double val_t;
typedef size_t ref_t;

class List {
public: 
    struct Node {
       val_t val;
       ref_t next;
       ref_t prev;
    };

    static constexpr ref_t DEFAULT_CAPACITY = 32u;
    static constexpr ref_t BAD_REF = (ref_t)-1;   
    
public:
    explicit List (ref_t cap = List::DEFAULT_CAPACITY);
    List (const std::initializer_list<val_t> &init_list);  

    ref_t head() const;
    ref_t tail() const;
    ref_t next (ref_t ref) const;
    ref_t prev (ref_t ref) const;
    val_t &get (ref_t ref);
    const val_t &get (ref_t ref) const;
    ref_t size() const;

    ref_t insert_front (val_t val);
    ref_t insert_back (val_t val);
    ref_t insert_after (ref_t ref, val_t val);
    ref_t insert_before (ref_t ref, val_t val);
    ref_t erase (ref_t ref);
    gv_Graph list_to_gv_graph() const;
    
    bool is_valid_ref (ref_t ref) const;

private:
    struct Buffer {
        Node *data;
        size_t capacity;

        Buffer (size_t sz = List::DEFAULT_CAPACITY);
        Buffer (const Buffer &another) = delete;
        Buffer & operator= (const Buffer &another) = delete;
        Buffer (Buffer &&another) = delete;
        Buffer & operator= (Buffer &&another) = delete;
       ~Buffer ();
        void swap (Buffer &another);
        Node &operator[] (size_t idx);
        const Node &operator[] (size_t idx) const;
    };
    Buffer m_buffer;
    ref_t m_ghost;  // Ref to ghost element for loop the list. Next is head and prev is tail;  
    ref_t m_free_head_ref;
    ref_t m_size;

    ref_t ghost() const;
    void set_head (ref_t ref);
    void set_tail (ref_t ref);
    ref_t free_head() const;
    void  shift_free_head();
    ref_t allocate_val (val_t val);
    bool is_full (ref_t free_head);
};

#endif