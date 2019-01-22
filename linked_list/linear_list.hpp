#ifndef _LINEAR_LIST_H
#define _LINEAR_LIST_H

template< class T, class P>
class Linear_list{
public:
    typedef T value_type;
    typedef P position;

    // Operators
    virtual void create() = 0;
    virtual bool empty() const = 0;
    virtual value_type read(position) const = 0;
    virtual void write(const value_type &, position) = 0;
    virtual position begin() const = 0;
    virtual bool end(position) const = 0;
    virtual position next(position) const = 0;
    virtual position previous(position) const = 0;
    virtual void insert(const value_type &, position p) = 0;
    virtual void erase(position) = 0;

    // Other Operators
    virtual int size() const = 0;
};
#endif // _LINEAR_LIST_H