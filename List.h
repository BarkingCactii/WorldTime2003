//
//
//   LIST.H
//
//	Linked List Container Class
//
//	Developed by: Jeff Hill of PCM COMPUTER SYSTEMS Pty Ltd
//
//

#ifndef _LIST_H
#define _LIST_H

//#include  "str.h"

enum ListPosition { Head, Tail };
enum VarType { Allocated, Stacks, Global };

/*
 *   LinkField stores the relationships between nodes
 */

struct LinkField
{
     LinkField *next;
     LinkField *previous;
};


/*
 *   ListData stores the user data for each node. Though complex 
 *   structures can be stored in a node, it is recommended to store 
 *   a pointer to the user data
 */

template<class T>
struct ListData : public LinkField
{
     T         userData;
     VarType   allocationMethod;

     ListData ( const T newItem, VarType memType = Allocated )
     {
          userData = newItem;
          allocationMethod = memType;
     }
};


/*
 *   ListCollection forms the collection of node into a list
 *   and provides means to manipulate user data within the list
 */

class ListCollection
{
     friend class ListBaseIterator;

private:
     LinkField *head;
     LinkField *tail;
public:
     void      Add ( void *, VarType );     
     void      Insert ( void *, VarType );     
     void      Insert ( void *, int, VarType );     
     void      MoveToEnd ( void * );
     void      Move ( int, int );
     void      Delete ( void * );
     long      Size ( void );
     long      Element ( LinkField * );
//     void      Swap ( String *, String * );
     void*     Nth ( int );
     VarType   AllocationMethod ( void * );
//     long      Match ( String& );

     ListCollection ( void );
    ~ListCollection ( void );

};


/*
 *   Iterator for a Linked List
 */

class ListBaseIterator
{
private:
     LinkField           *currentNode;
     ListCollection      *whichList;
public:
     ListBaseIterator ( ListCollection& s );

     inline    LinkField* operator ++ ( void )
     {
          if ( currentNode == whichList->tail )
               return ( 0 );

          LinkField*     current = currentNode;

          currentNode = currentNode->next;

          return ( current );
     }

     inline    LinkField* operator -- ( void )
     {
          if ( currentNode == whichList->head )
               return ( 0 );

          LinkField*     current = currentNode;

          currentNode = currentNode->previous;

          return ( current );
     }

     void Seek ( ListPosition, int );

     inline    LinkField* Current ( void )
     {
          return (( currentNode == whichList->head || currentNode == whichList->tail ) ? 0 : currentNode );
     }
};



/*
 *   User class to define a doubly linked list
 */

template<class T>
class LinkedList : public ListCollection
{
//friend class ListIterator<T>;
protected:
public:
     LinkedList ( void ) { }

     //   destructor
    ~LinkedList ( void )
     {
          T    userData;

          int  i = 0;

          while (( userData = Nth ( i++ )) != 0 )
          {
               if ( ListCollection::AllocationMethod ( userData ) == Allocated )
                    delete userData;
          }
     }

     //   Add a node to end of list
     void      Add ( const T newItem, VarType allocated = Allocated )
     {
          ListCollection::Add ( newItem, allocated );
     }

     //   Insert a node at start of list
     void      Insert ( const T newItem, VarType allocated )
     {
          ListCollection::Insert ( newItem, allocated );
     }

     //   Insert a node at specified position in list
     void      Insert ( const T newItem, int pos, VarType allocated = Allocated )
     {
          ListCollection::Insert ( newItem, pos, allocated );
     }

     //   Move a node to end of list
     void      MoveToEnd ( T aItem )
     {
          ListCollection::MoveToEnd ( aItem );
     }

     //   Move a node to any positiont
     void      Move ( int from, int to )
     {
          ListCollection::Move ( from, to );
     }


     //   Delete a node from the list
     void      Delete ( T oldItem )
     {
//         T item = oldItem;
        VarType allocated = ListCollection::AllocationMethod ( oldItem );
        ListCollection::Delete ( oldItem );
        if ( allocated == Allocated )
            delete oldItem;
/*          if ( ListCollection::AllocationMethod ( oldItem ) == Allocated )
               delete oldItem;
          ListCollection::Delete ( item ); //oldItem );
          */
     }

     //   Get number of elements in list
     inline long Size ( void )
     {
          return ( ListCollection::Size ());
     }

     //   Get the n'th element
     inline T Nth ( int whichNode )
     {
          return (( T ) ListCollection::Nth ( whichNode ));
     }

     inline void Clear ( void )
     {
          T    userData;

          while (( userData = Nth ( 0 )) != 0 )
          {
               if ( ListCollection::AllocationMethod ( userData ) == Allocated )
                    delete userData;
               Delete ( userData );
          }
     }

     //   Return the index number for the node
     //   Really only applies to lists of pointers 
     inline long Element ( T item )
     {
          return ( ListCollection::Element (( LinkField * ) item ));
     }

};
/*
#ifndef PC_DOS

template<class T>
void LinkedList<T>::Delete ( T oldItem )
{
     if ( ListCollection::AllocationMethod ( oldItem ) == Allocated )
          delete oldItem;
     ListCollection::Delete ( oldItem );

}

template<class T>
LinkedList<T>::~LinkedList ( void )
{
      T    userData;

      int  i = 0;

      while (( userData = Nth ( i++ )) != 0 )
      {
           if ( ListCollection::AllocationMethod ( userData ) == Allocated )
                delete userData;
      }

//          ListCollection::Clear ();
}

#endif
*/
/*
 *   User class for a Linked List Iterator
 */

template<class T>
class ListIterator : private ListBaseIterator
{
public:
     //   Link to a specified List
//     ListIterator ( LinkedList<T>& whichlist );
     ListIterator ( LinkedList<T>& whichList ) : ListBaseIterator ( whichList ) {}

     //   Get next node in list
     inline T operator ++ ( int )
     {
          ListData<T>* node = ( ListData<T>* ) ListBaseIterator::operator ++ ();
          return ( node ? (T) node->userData : (T) 0 );
     };

     //   Get previous node in list
     inline T operator -- ( int )
     {
          ListData<T>* node = ( ListData<T>* ) ListBaseIterator::operator -- ();
          return ( node ? (T) node->userData : (T) 0 );
     }

     //   Seek to specific node
     inline void Seek ( ListPosition newPos , int offset = 0 )
     {
          ListBaseIterator::Seek ( newPos, offset );
     }

     //   Get the current node
     inline T Current ( void )
     {
          ListData<T>* node = ( ListData<T>* ) ListBaseIterator::Current ();
          return ( node ? (T) node->userData : (T) 0 );
     }
};
/*
class StringList : public LinkedList<String*>
{
     friend class StringListIterator;
public:
     void Sort ( void );

     long Match ( String& src ) 
     { 
          return ( ListCollection::Match ( src ));
     }

     //   Swap 2 nodes
     inline void Swap ( String * node1, String * node2 )
     {
          ListCollection::Swap ( node1, node2 );
     }

     StringList ( void ) { }
    ~StringList ( void ) { }
};

class StringListIterator : public ListIterator<String*>
{
public:
     StringListIterator ( StringList& whichList ) : ListIterator<String*> ( whichList ) {};
    ~StringListIterator ( void ) { }
};
  */
//
//   A Stack list. 
//   Note: Declare the stack as a type of the data to be stored, not a
//   pointer to the type being stored. A compile error will result if
//   you try to do this anyway. There is no need to allocate memory for
//   data before pushing on the stack. This is done by the Stack.
//   This is because a stack will usually be popping onto the same data
//   area. For example:
//   
//   Stack<short> aStack;
//   short     s1;
//   
//   s1 = 1;
//   aStack.Push ( &s1 );
//   s1 = 2;
//   aStack.Push ( &s1 );
//
//   do 
//   {
//   }
//   while ( aStack.Pop ( &s1 ));
//

template<class T>
class Stack : protected LinkedList<T*>
{
public:
     Stack ( void ) { }
    ~Stack ( void ) { }

     inline long Size ( void )
     {
          return LinkedList<T*>::Size ();
     }

     inline void Push ( const T* newData ) 
     {
          T* newItem = new T;
          *newItem = *newData;
          Add ( newItem, Allocated );
     }

     inline T* Pop ( T* storedData ) 
     {
          if ( Size() <= 0 )
               return 0;

          T* storedItem;
          storedItem = Nth ( Size () - 1 );
          if ( storedItem )
          {
               *storedData = *storedItem;
               Delete ( storedItem );
          }
          return storedData;
     }
};

template<class T>
class PtrStack : public LinkedList<T>
{
public:
     PtrStack ( void ) { }
    ~PtrStack ( void ) { }

     inline void PushPtr ( const T newData ) 
     {
          Add ( newData, Allocated );
     }

     inline T PopPtr ( void )
     {
          if ( Size() <= 0 )
               return 0;

          T storedItem;
          storedItem = Nth ( Size () - 1 );

          return storedItem;
     }

     void Pop ( void )
     {
          if ( Size() <= 0 )
               return;

          T storedItem;
          storedItem = Nth ( Size () - 1 );
          if ( storedItem )
               Delete ( storedItem );
     }

};

//
//   A Queue list. 
//   Note: Declare the queue as a type of the data to be stored, not a
//   pointer to the type being stored. A compile error will result if
//   you try to do this anyway. There is no need to allocate memory for
//   data before pushing on the queue. This is done by the Queue.
//   This is because a queue will usually be popping onto the same data
//   area. For example:
//   
//   Queue<short> aQueue;
//   short     s1;
//   
//   s1 = 1;
//   aQueue.Push ( &s1 );
//   s1 = 2;
//   aQueue.Push ( &s1 );
//
//   do 
//   {
//   }
//   while ( aQueue.Pop ( &s1 ));
//

template<class T>
class Queue : protected LinkedList<T*>
{
public:
     Queue ( void ) { }
    ~Queue ( void ) { }

     inline void Push ( const T* newData ) 
     {
          T* newItem = new T;
          *newItem = *newData;
          Add ( newItem, Allocated );
     }

     inline T* Pop ( T* storedData ) 
     {
          T* storedItem;
          storedItem = this->Nth ( 0 );
          if ( !storedItem )
               return 0;

          *storedData = *storedItem;
          Delete ( storedItem );
          return storedData;
     }

     //   Get the n'th element
     inline T* Nth ( int whichNode )
     {
          return (( T* ) ListCollection::Nth ( whichNode ));
     }

     //   Get the queue size
     inline long Size ( void )
     {
          return ( ListCollection::Size () );
     }
};


template<class T>
class LArray : public LinkedList<T>
{
public:
     inline
     T & operator () ( int i1, int i2 = 0, int i3 = 0, int i4 = 0, int i5 = 0 )
     {
          if (( i1 >= size[0] ) ||
             (  i2 && i2 >= size[1] ) ||
             (  i3 && i3 >= size[2] ) ||
             (  i4 && i4 >= size[3] ) ||
             (  i5 && i5 >= size[4] ))
             {
               DisplayError ();
               exit ( 1 );
             }

          return data[CalcOffset ( i1, i2, i3, i4, i5 )];
     }

     LArray ( void ) { }
    ~LArray ( void ) { }
};

#endif
