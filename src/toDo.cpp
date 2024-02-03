#include "toDo.hpp"
#include <cstdlib>

struct Cella{
    toDo info;
    Cella* next;
    Cella* prev;
};
typedef Cella* PCella;

struct toDo::impl{
    std::string str;
    int id;
    bool completed;
    
    PCella head;
    PCella tail;
};

struct toDo::list_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = toDo;
    using pointer = toDo*;
    using reference = toDo&;
    
    list_iterator(PCella ptr);
        
    reference operator*() const;
    
    pointer operator->() const;
    
    list_iterator& operator++ ();
    
    list_iterator operator++ (int /* dummy */);
    
    bool operator==(list_iterator const& rhs) const;
    bool operator!=(list_iterator const& rhs) const;
    operator bool() const;
    
private:
    PCella m_ptr;
};

struct toDo::const_list_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = toDo const;
    using pointer = toDo const*;
    using reference = toDo const&;
    
    const_list_iterator(PCella const ptr);
        
    reference operator*() const;
    
    pointer operator->() const;
    
    const_list_iterator& operator++ ();
    
    const_list_iterator operator++ (int /* dummy */);
        
    bool operator==(const_list_iterator const& rhs) const;
    bool operator!=(const_list_iterator const& rhs) const;
    operator bool() const;
    
private:
    Cella const* m_ptr;
};

toDo::list_iterator::list_iterator(PCella ptr) : m_ptr(ptr) {}

toDo::list_iterator::reference toDo::list_iterator::operator*() const {
    return m_ptr->info;
}

toDo::list_iterator::pointer toDo::list_iterator::operator->() const {
    return &(m_ptr->info);
}

toDo::list_iterator& toDo::list_iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

toDo::list_iterator toDo::list_iterator::operator++(int) {
    list_iterator tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
}

bool toDo::list_iterator::operator==(list_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

bool toDo::list_iterator::operator!=(list_iterator const& rhs) const {
    return !(*this == rhs);
}

toDo::list_iterator::operator bool() const {
    return m_ptr != nullptr;
}

toDo::list_iterator toDo::begin_list() {
    return {pimpl->head};
}

toDo::list_iterator toDo::end_list() {
    return {nullptr};
}

toDo::const_list_iterator::const_list_iterator(PCella ptr) : m_ptr(ptr) {}

toDo::const_list_iterator::reference toDo::const_list_iterator::operator*() const {
    return m_ptr->info;
}

toDo::const_list_iterator::pointer toDo::const_list_iterator::operator->() const {
    return &(m_ptr->info);
}

toDo::const_list_iterator& toDo::const_list_iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

toDo::const_list_iterator toDo::const_list_iterator::operator++(int) {
    const_list_iterator tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
}

bool toDo::const_list_iterator::operator==(const_list_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

bool toDo::const_list_iterator::operator!=(const_list_iterator const& rhs) const {
    return !(*this == rhs);
}

toDo::const_list_iterator::operator bool() const {
    return m_ptr != nullptr;
}

toDo::const_list_iterator toDo::begin_list() const{
    return {pimpl->head};
}

toDo::const_list_iterator toDo::end_list() const {
    return {nullptr};
}

void clear(PCella& head, PCella& tail) {
    PCella pc = head;
    while(pc) {
        pc = pc->next;
        delete head;
        head = pc;
    }
    head = nullptr;
    tail = nullptr;
}

void clearScreen() {
    std::system("clear");
}

toDo::toDo() {
    pimpl = new impl;
    
    pimpl->str = "";
    pimpl->id = 0;
    pimpl->head = nullptr;
    pimpl->tail = nullptr;
    pimpl->completed = false;
}

toDo::toDo(toDo const& val) : toDo() {
    pimpl->str = val.pimpl->str;
    pimpl->id = val.pimpl->id;
    pimpl->completed = val.pimpl->completed;
    pimpl->head = val.pimpl->head;
    pimpl->tail = val.pimpl->tail;
    
    PCella tmp = val.pimpl->head;
    while(tmp) {
        push_back(tmp->info);
        tmp = tmp->next;
    }
}

toDo::toDo(toDo&& val) : toDo() {
    pimpl->head = val.pimpl->head;
    pimpl->tail = val.pimpl->tail;
    
    val.pimpl->head = nullptr;
    val.pimpl->tail = nullptr;
    
    pimpl->str = val.pimpl->str;
    pimpl->id = val.pimpl->id;
    pimpl->completed = val.pimpl->completed;
}

toDo::~toDo() {
    clear(pimpl->head, pimpl->tail);
    delete pimpl;
}

toDo& toDo::operator=(toDo const& val) {
    if(this != &val) {
        clear(pimpl->head, pimpl->tail);
        
        pimpl->id = val.pimpl->id;
        pimpl->str = val.pimpl->str;
        pimpl->completed = val.pimpl->completed;

        PCella tmp = val.pimpl->head;
        while(tmp) {
            push_back(tmp->info);
            tmp = tmp->next;
        }
    }
    return *this;
}

toDo& toDo::operator=(toDo&& val) {
    if(this != &val) {
        clear(pimpl->head, pimpl->tail);
        
        pimpl->head = val.pimpl->head;
        pimpl->tail = val.pimpl->tail;
        val.pimpl->head = nullptr;
        val.pimpl->tail = nullptr;
        
        pimpl->id = val.pimpl->id;
        pimpl->str = val.pimpl->str;
        pimpl->completed = val.pimpl->completed;
    }
    return *this;
}

bool toDo::is_completed() const {
    return pimpl->completed;
}

int& toDo::get_id() {
    return pimpl->id;
}

int const& toDo::get_id() const {
    return pimpl->id;
}

std::string& toDo::get_string() {
    return pimpl->str;
}

std::string const& toDo::get_string() const {
    return pimpl->str;
}

void toDo::set_string(std::string const& str) {
    clear(pimpl->head, pimpl->tail);
    
    static int uniqueID = 0;
    pimpl->id = ++uniqueID;
    
    pimpl->str = str;
    pimpl->completed = false;
}

void toDo::set_completed() {
    pimpl->completed = true;
}


void toDo::push_back(toDo const& val) {
    PCella nuovo = new Cella;
    nuovo->info = val;
    nuovo->next = nullptr;
    nuovo->prev = pimpl->tail;

    if (!pimpl->head) {
        pimpl->head = nuovo;
        pimpl->tail = nuovo;
    } else {
        pimpl->tail->next = nuovo;
        pimpl->tail = nuovo;
    }
}

bool toDo::isEmpty() {
    return pimpl->head == nullptr;
}
