/*
 *
 *   LIST.CPP
 *
 *	Linked List Container Class member functions
 *
 *	Developed by: Jeff Hill of PCM COMPUTER SYSTEMS P/L for REOFORCE SYSTEMS P/L
 *
 */

#include  "stdafx.h"
#include  <stdio.h>
#include  <stdlib.h>
#include  <iostream>
#include  <new.h>
//#include  <string.h>
#include  "list.h"
//#include  "str.h"

/*
 *   ListCollection member functions
 */

//ListIterator::ListIterator ( LinkedList<T>& whichList ) : ListBaseIterator ( whichList ) {}
//ListIterator::ListIterator ( LinkedList<T>& whichList )
//{
//     ListBaseIterator ( whichList );
//}

ListCollection::ListCollection ( void )
{
     head = new LinkField;
     tail = new LinkField;

     head->previous = 0;
     head->next = tail;

     tail->previous = head;
     tail->next = 0;
}

ListCollection::~ListCollection ( void )
{
     LinkField *current = head->next;

     delete head;

     while ( current != tail )
     {
          LinkField *nextNode = current->next;

          delete current;
          current = nextNode;
     }

     delete tail;
}

void ListCollection::Add ( void *userData, VarType allocated )
{
     LinkField* newNode = new ListData<void*> ( userData, allocated );

     tail->previous->next = newNode;
     newNode->previous = tail->previous;
     tail->previous = newNode;
     newNode->next = tail;
}

void ListCollection::Insert ( void *userData, VarType allocated )
{
     LinkField* newNode = new ListData<void*> ( userData, allocated );

     head->next->previous = newNode;
     newNode->next = head->next;
     head->next = newNode;
     newNode->previous = head;
}

void ListCollection::MoveToEnd ( void *userData )
{
     LinkField *current = head->next;

     while ( current != tail )
     {
          ListData<LinkField*>* listData = ( ListData<LinkField*>* ) current;

          if ( listData->userData == userData )
          {
               current->previous->next = current->next;
               current->next->previous = current->previous;

               current->next = tail;
               current->previous = tail->previous; 

               tail->previous->next = current;
               tail->previous = current;

               break;
          }
          current = current->next;
     }
}

void ListCollection::Move ( int from, int to )
{

     LinkField *fromP = head->next;
     LinkField *toP = head->next;

	 if ( from == to )
		 return;

	 for ( int i = 0; i < from; i++ )
	 {
		 if ( fromP )
			 fromP = fromP->next;
		 else
			 return;
	 }

	 for ( i = 0; i < to; i++ )
	 {
		 if ( toP )
			 toP = toP->next;
		 else
			 return;
	 }
/*
     ListData<LinkField*>* listDataFrom = ( ListData<LinkField*>* ) fromP;
     ListData<LinkField*>* listDataTo = ( ListData<LinkField*>* ) toP;

     //ListData<LinkField*>* listDataTo = ( ListData<LinkField*>* ) toP;
	 LinkField * tmp = listDataFrom->userData;
//	 LinkDataTo->userData = listDataFrom->userData;
	 listDataFrom->userData = listDataTo->userData;
	 listDataTo->userData = tmp;
	 */
	 
	 // re-route the pointers

	 fromP->next->previous = fromP->previous;
	 fromP->previous->next = fromP->next;

//	 toP->next->previous = fromP;
	 toP->previous->next = fromP;

	 fromP->next = toP;
	 fromP->previous = toP->previous;

	 toP->previous = fromP;

/*	 LinkField * tN = toP->next;
	 LinkField * tP = toP->previous;

	 toP->next = fromP->next;
	 toP->previous = fromP->previous;

	 fromP->next = tN;
	 fromP->previous = tP;
  */
	 
}


void ListCollection::Insert ( void *userData, int pos, VarType allocated )
{
     LinkField* newNode = new ListData<void*> ( userData, allocated );

     LinkField* insertNode = head->next;
     for ( int i = 0; i < pos; i++ )
     {
          insertNode = insertNode->next;
          if ( insertNode == 0 )
          {
               // insert at end and abort
               tail->previous->next = newNode;
               newNode->previous = tail->previous;
               tail->previous = newNode;
               newNode->next = tail;
               return;
          }
     }

     newNode->next = insertNode;
     newNode->previous = insertNode->previous;
     insertNode->previous->next = newNode;
     insertNode->previous = newNode;
}

VarType ListCollection::AllocationMethod ( void* userData )
{
     LinkField *current = head->next;

     while ( current != tail )
     {
          ListData<LinkField*>* listData = ( ListData<LinkField*>* ) current;

          if ( listData->userData == userData )
               return ( listData->allocationMethod );

          current = current->next;
     }

     return ( Global );
}

void ListCollection::Delete ( void* userData )
{
     LinkField *current = head->next;

     while ( current != tail )
     {
          ListData<LinkField*>* listData = ( ListData<LinkField*>* ) current;

          if ( listData->userData == userData )
          {
               current->previous->next = current->next;
               current->next->previous = current->previous;
               delete current;
               break;
          }
          current = current->next;
     }
}

long ListCollection::Size ( void )
{
     long  numNodes = 0;

     LinkField *current = head->next;

     while ( current != tail )
     {
          numNodes++;
          current = current->next;
     }

     return ( numNodes );
}

long ListCollection::Element ( LinkField *item )
{
     long  numNodes = 0;

     LinkField *current = head->next;
     ListData<LinkField*>* listData = ( ListData<LinkField*>* ) current;

     while ( listData->userData != item )
     {
          numNodes++;
          current = current->next;
          if ( current == 0 )
               return 0;

          listData = ( ListData<LinkField*>* ) current;
     }

     if ( listData->userData == item )
          return ( numNodes );


     return ( 0 );
}

/*
long ListCollection::Match ( String& src )
{
     long  numNodes = 0;
     LinkField *current = head->next;

     while ( current != tail )
     {
          ListData<String*>* listData = ( ListData<String*>* ) current;
//          ListData<LinkField*>* listData = ( ListData<LinkField*>* ) current;

          String* curr = listData->userData;
//          debug << "src [" << src << "] list elem " << numNodes << " = [" << *curr << "]" << endl << flush;
//          debug << "src [" << src << "] list elem " << numNodes << " = [" << *curr << "]" << endl << flush;
          if ( *curr == src )
          {
  //             debug << "Found a match " << *curr << " " << src << endl;
               return ( numNodes );
          }
          numNodes++;
          current = current->next;
     }
     return ( 0 );
}
  */
void* ListCollection::Nth ( int whichNode )
{
     if ( head->next == tail )
          return ( 0 );

     int  numNodes = 0;

     LinkField *current = head->next;

     while ( numNodes != whichNode )
     {
          numNodes++;
          current = current->next;

          if ( current == tail )
               return ( 0 );
     }

     ListData<LinkField*>* listData = ( ListData<LinkField*>* ) current;
     return ( listData->userData );
}
/*
void ListCollection::Swap ( String *node1, String *node2 )
{
//     LinkField *tmpnext;
//     LinkField *tmpprev;

//     tmpnext = node1->next;
//     tmpprev = node1->previous;

//     node1->next = node2->next;
//     node1->previous = node2->previous;

//     node2->next = tmpnext;
//     node2->previous = tmpprev;

     String **nn1 = ( String ** )node1;
     String **nn2 = ( String ** )node2;

     LinkField *current = head->next;
     LinkField *n1 = 0;
     LinkField *n2 = 0;

     while ( current != tail )
     {
          ListData<LinkField*>* listData = ( ListData<LinkField*>* ) current;

          if ( listData->userData == ( LinkField * ) node1 )
          {
               n1 = current;
          }
          else
          if ( listData->userData == ( LinkField * ) node2 )
          {
               n2 = current;
          }

          if ( n1 && n2 )
          {
               LinkField * tmpNext;
               LinkField * tmpPrev;

               tmpNext = n1->next;
               tmpPrev = n1->previous;

               n1->previous = n2->previous;
               n1->next = n2->next;

               n2->previous = tmpPrev;
               n2->next = tmpNext;

               return;
          }               

          current = current->next;
     }
}
  */
/*
 *   ListBaseIterator member functions
 */

void ListBaseIterator::Seek ( ListPosition newPos, int offset )
{
     if ( newPos == Head )
     {
          currentNode = whichList->head->next;

          for ( int i = 0; i < offset; i++ )
          {
               if ( currentNode != whichList->tail )
                    currentNode = currentNode->next;
          }
     }

     if ( newPos == Tail )
     {
          currentNode = whichList->tail->previous;

          for ( int i = 0; i < offset; i++ )
          {
               if ( currentNode != whichList->head )
                    currentNode = currentNode->previous;
          }
     }
}

ListBaseIterator::ListBaseIterator ( ListCollection& s )
{
     whichList = &s;

     currentNode = whichList->head->next;
}

