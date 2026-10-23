#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc >= size_)
  {
    return NULL;
  }

  Item* curr = head_;
  while(curr != NULL)
  {
    size_t node_members = curr->last - curr->first;
    if(loc < node_members)
    {
      return &curr->val[curr->first + loc];
    }
    else
    {
      loc = loc - node_members;
      curr = curr->next;
    }
  }
  return NULL;
}

void ULListStr::push_back(const std::string& val)
{
  if(empty() || tail_->last >= ARRSIZE)
   {
    Item* new_node = new Item();
    if(empty())
    {
      head_ = new_node;
      tail_ = new_node;
    }
    else
    {
      tail_->next = new_node;
      new_node->prev = tail_;
      tail_ = new_node;
    }
   }

   tail_->val[tail_->last] = val;
   tail_->last++;
   size_++;
}

void ULListStr::push_front(const std::string& val)
{
  if(empty() || head_->first == 0)
   {
    Item* new_node = new Item();
    new_node->first = ARRSIZE;
    new_node->last = ARRSIZE;

    if(empty())
    {
      head_ = new_node;
      tail_ = new_node;
    }
    else
    {
      head_->prev = new_node;
      new_node->next = head_;
      head_ = new_node;
    }
   }

   head_->first--;
   head_->val[head_->first] = val;
   
   size_++;
}

void ULListStr::pop_back()
{
  if(empty())
  {
    return;
  }
  tail_->last--;
  size_--;

  if(tail_->first == tail_->last)
  {
    if(head_ == tail_)
    {
      delete tail_;
      tail_ = NULL;
      head_ =NULL;
    }
    else
    {
      Item* old_tail = tail_;  
      tail_ = tail_->prev; 
      tail_->next = NULL;  
      delete old_tail;
    }
  }
}

void ULListStr::pop_front()
{
  if(empty())
  {
    return;
  }
  head_->first++;
  size_--;

  if(head_->first == head_->last)
  {
    if(head_ == tail_)
    {
      delete head_;
      tail_ = NULL;
      head_ = NULL;
    }
    else
    {
      Item* old_head = head_;  
      head_ = head_->next; 
      head_->prev = NULL;  
      delete old_head;
    }
  }
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1];
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
