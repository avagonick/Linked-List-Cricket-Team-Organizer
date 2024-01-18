//
//  CricketTeam.cpp
//  Project 2 CS32
//
//  Created by Ava Gonick on 7/9/23.
//

#include "CricketTeam.h"
#include <string>
using namespace std;

//default constructor
CricketTeam::CricketTeam(){
    head = nullptr;
    tail = nullptr;

 
}

CricketTeam::CricketTeam(const CricketTeam& copy ){
    //if copying over a set everything to the nullptr and return 
    if(copy.head == nullptr && copy.tail == nullptr){
        head = nullptr;
        tail = nullptr;
        
    
        return;
    }
    head = new Node;
    Node* current  = head;
    Node* prev = nullptr;
    Node* loop = copy.head;
    //loop through the copy linkedlist stopping at the last node because this needs to by done slightly differently
    while( loop != copy.tail){
        //copy over values
        current -> first = loop -> first;
        current -> last = loop -> last;
        current -> val = loop -> val;
        //set previous to the previous node
        current -> previous = prev;
        //create a new node to set the enxt node
        Node* after = new Node;
        current -> next = after;
        prev = current;
        current = after;
        loop = loop -> next;
    }
    current -> first = loop -> first;
    current -> last = loop -> last;
    current -> val = loop -> val;
    current -> previous = prev;
    current -> next = nullptr;
    tail = current;
    
    

}

bool CricketTeam::noTeam() const{
    if(head == nullptr && tail == nullptr)
        return true;
    else
        return false;
}

int CricketTeam::cricketerCount() const{
    Node * loop = head;
    int counter = 0;
    while( loop != nullptr){
        counter ++;
        loop = loop -> next;
    }
    return counter;
}

bool CricketTeam::addCricketer(const std::string& firstName, const std::string& lastName, const CricketType& value){
    
    //if empty list add the node in
    if( head == nullptr && tail == nullptr){
        Node* add = new Node;
        add -> first = firstName;
        add -> last = lastName;
        add -> val = value;
        add -> previous = nullptr;
        add -> next = nullptr;
        head = add;
        tail = add;
        return true;
    }
    //check if the cricketer is already in the list if so return
    Node * loop = head;
    while( loop != nullptr){
        if(loop -> first == firstName && loop -> last == lastName /*&& loop-> val == value*/) //double check but it says don't add if same name diff value 
            return false;
        loop = loop -> next;
    }
    
    //if the value is the smallest in the list add it to the front and reset the head
    if( (lastName < head ->last) || ( lastName == head -> last && firstName < head -> first) ){
        Node* add = new Node;
        add -> last = lastName;
        add ->first = firstName;
        add -> val = value;
        add -> next = head; 
        head -> previous = add;
        head = add;
        head -> previous = nullptr;
        return true;
    }
    
    //loop through the Linked List to figure out where to put the new Node
    Node* check = head;
    while( check != tail){
        
        //if the last name is greater than the current last name but less than the next last name create a new node and add it into the linked list
        if( lastName > check -> last && lastName < check -> next -> last){
            Node* add = new Node;
            add -> last = lastName;
            add ->first = firstName;
            add -> val = value;
            add-> previous = check;
            add -> next = check -> next;
            check -> next -> previous = add;
            check -> next = add;
            return true;
        }
        //if last names are the same then have to look at first names
        if(lastName == check -> last){
            Node* innerloop = check;
            while(innerloop != tail){
                //if the first name is greater than the current first name and the next last name is greater
                if(firstName > innerloop->first && lastName < innerloop -> next -> last){
                    Node* add = new Node;
                    add -> last = lastName;
                    add ->first = firstName;
                    add -> val = value;
                    add -> previous = innerloop;
                    add -> next = innerloop -> next;
                    innerloop -> next -> previous = add;
                    innerloop -> next = add;
                    return true;
                }
                //if the first name is greater than the current first name but smaller than the next first name and the next last name is the same
                if(firstName > innerloop -> first && firstName < innerloop -> next -> first && lastName == innerloop -> next -> last){
                    Node* add = new Node;
                    add -> last = lastName;
                    add ->first = firstName;
                    add -> val= value;
                    add -> previous = innerloop;
                    add -> next = innerloop -> next;
                    innerloop -> next -> previous = add;
                    innerloop -> next = add;
                    return true;
                }
                //if first name is less than the current first name and the next last name is greater then create a new node add it into the linked list
                if(firstName < innerloop -> first ){
                    Node* add = new Node;
                    add -> last = lastName;
                    add ->first = firstName;
                    add -> val = value;
                    add -> next = innerloop;
                    add -> previous = innerloop -> previous;
                    innerloop -> previous -> next = add;
                    innerloop -> previous = add;
                    
                    return true;
                }
            
               
                innerloop = innerloop -> next;
            }
        }
        check = check -> next;
    }
    //out of the loop means that this value must be the greatest value, or has the same last name and could be less then
    
    //check if same last name this is the only case that it could be less than
    if(check->last == lastName && firstName < check->first){
        Node* add = new Node;
        add -> last = lastName;
        add ->first = firstName;
        add -> val = value;
        check ->previous -> next = add;
        add -> previous = check->previous;
        add -> next = check;
        check -> previous = add;
        return true; 
        
    }
    
    //every other situation if got to the end it is the greatest value in the list 
    Node* add = new Node;
    add -> last = lastName;
    add ->first = firstName;
    add -> val = value;
    add -> previous = tail;
    add -> next = nullptr;
    tail -> next = add;
    tail = add;
    return true; 
    
}

//destructor
CricketTeam::~CricketTeam(){
    Node* loop = head;
    while (loop != nullptr){
        Node* hold = loop ->next;
        delete loop;
        loop = hold;
    }
    

    
}

//assignment opereator

CricketTeam& CricketTeam::operator=(const CricketTeam& rhs){
    //if the two Cricket Teams are the same return
    if(this == &rhs)
        return *this;
    
    //delete the current values
    Node* todelete = head;
    while (todelete != nullptr){
        Node* hold = todelete ->next;
        delete todelete;
        todelete = hold;
    }
    
    if(rhs.head == nullptr && rhs.tail == nullptr){
        head = nullptr;
        tail = nullptr;
        return * this;
    }
    
    head = new Node;
    Node* current  = head;
    Node* prev = nullptr;
    Node* loop = rhs.head;
    //loop through the copy linkedlist stopping at the last node because this needs to by done slightly differently
    while( loop != rhs.tail){
        //copy over values
        current -> first = loop -> first;
        current -> last = loop -> last;
        current -> val = loop -> val;
        //set previous to the previous node
        current -> previous = prev;
        //create a new node to set the enxt node
        Node* after = new Node;
        current -> next = after;
        prev = current;
        current = after;
        loop = loop -> next;
    }
    current -> first = loop -> first;
    current -> last = loop -> last;
    current -> val = loop -> val;
    current -> previous = prev;
    current -> next = nullptr;
    tail = current;
    

    return *this; 
}

bool CricketTeam::substituteCricketer(const std::string& firstName, const std::string& lastName, const CricketType& value){
    Node* loop = head;
    while(loop != nullptr){
        if(firstName == loop->first&& lastName == loop -> last){
            loop -> val = value;
            return true;
        }
        loop = loop -> next;
    }
    return false;
}

bool CricketTeam::addOrSubstitute(const std::string& firstName, const std::string& lastName, const CricketType& value){
    Node* loop = head;
    //loop through and see if the Cricketer already exists, if it does just substitute
    while(loop != nullptr){
        if(firstName == loop->first && lastName == loop -> last){
            loop -> val = value;
            return true;
        }
        loop = loop -> next;
    }
    
    //if the Cricketer doesn't already exist add one to the end of the Linked List, can't do this have to add it in the correct place so
    addCricketer(firstName, lastName, value);
    return true;
}


bool CricketTeam::releaseCricketer(const std::string& firstName, const std::string& lastName){
    
    //loop through the linked list
    Node* loop = head;
    while(loop != nullptr){
        
        //if in the roster delete and return true
        //if delete value is tail
        if(loop -> first == firstName && loop -> last == lastName){
            if(loop == tail && loop == head){
                delete loop;
                head = nullptr;
                tail = nullptr;
                return true;
            }
            if(loop == tail){
                loop -> previous -> next = nullptr;
                tail = loop -> previous;
                delete loop;
                return true;
            }//if delete value is head
            if(loop == head){
                loop -> next -> previous = nullptr;
                head = loop -> next;
                delete loop;
                return true;
            }
            //if delete value is in the middle
            else{
                loop -> previous -> next = loop -> next;
                loop -> next -> previous = loop ->previous;
                delete loop;
                return true;
            }
        }
        
        loop = loop -> next;
    }
    
    //if went through the entire linked list and don't return it means it isn't in the linked list and return false 
    return false;
}


bool CricketTeam::rosteredOnCricketTeam(const std::string& firstName, const std::string& lastName) const{
    
    //loop through looking to see if it is rostered on the Cricket team 
    Node* loop = head;
    while(loop != nullptr){
        if(loop -> first == firstName && loop -> last == lastName){
            return true;
        }
        loop = loop -> next;
    }
    //if get here it wasn't found
    return false;
}

bool CricketTeam::searchForCricketer(const std::string& firstName, const std::string& lastName, CricketType& value) const{
    Node* loop = head;
    
    //loop through to see if it is roseterd on the Cricket team
    while(loop != nullptr){
        
        //if rostered set value
        if(loop -> first == firstName && loop -> last == lastName){
            value = loop -> val;
            return true;
        }
        loop = loop -> next;
    }
    
    //if get here not rostered so return false 
    return false;
}

bool CricketTeam::checkTeamForCricketer(int i, std::string& firstName, std::string& lastName, CricketType& value) const{
    //make sure i is in bounds
    if( i < 0 || i >= cricketerCount())
        return false;
    Node * loop = head;
    
    //loop through to the right i position
    int it;
    for( it = 0; it <i; it++){
        loop = loop -> next;
    }
    //at the right i position set the values
    firstName = loop -> first;
    lastName = loop -> last;
    value = loop -> val;
    return true;
    
}

void CricketTeam:: tradeCricketTeams (CricketTeam& other){
    //if trying to swap the same team just return 
    if (this == &other)
        return;

    //create nodes to hold the values
    Node* holdhead = head;
    Node* holdtail = tail;
    //set the current tail and head to the other tail and head
    tail = other.tail;
    head = other.head;
    //set the other tail and head to what was the current tail and head 
    other.tail = holdtail;
    other.head = holdhead;
}

bool mergeCricketers(const CricketTeam& odOne, const CricketTeam& odTwo, CricketTeam& odJoined){
    //need to be checked for aliasing
    //put items in a holding cricketTeam to make sure that it works properly if any aliasing 
    CricketTeam hold;
    
    
    //loopthrough odOne adding it to odJoined
    int team1size = odOne.cricketerCount();
    for( int i = 0; i < team1size; i++){
        string first;
        string last;
        CricketType vals;
        odOne.checkTeamForCricketer(i, first, last, vals);
        hold.addCricketer(first, last, vals);
    }
    
    bool nobadrepeat = true;
    //loop through odTwo adding nonrepeat team members  to odJoined
    int team2size = odTwo.cricketerCount();
    for( int i = 0; i < team2size; i++){
        string first;
        string last;
        CricketType vals;
        odTwo.checkTeamForCricketer(i, first, last, vals);
        //if there is a repeat team member check
        if(!hold.addCricketer(first, last, vals)){
            CricketType repeatval;
            hold.searchForCricketer(first, last, repeatval);
            //if repeat team member has a different value set no bad repeat to false so this returns false and delete the repeated value from odJoined
            if( vals != repeatval){
                nobadrepeat = false;
                hold.releaseCricketer(first, last);
                
            }
        }
    }
    hold.tradeCricketTeams(odJoined);
    return nobadrepeat; 
}

void checkCricketers(const string& fsearch, const string& lsearch, const CricketTeam& odOne, CricketTeam& odResult){
    //need to be fixed for aliasing
    //add things to hold and then switch
    //make sure odResult is empty
    CricketTeam hold;

    
    //loop through odOne
    int teamSize = odOne.cricketerCount();
    for( int i = 0; i < teamSize; i++){
        string first;
        string last;
        CricketType vals;
        odOne.checkTeamForCricketer(i, first, last, vals);
        //if the name matches
        if((first == fsearch || fsearch == "*") && (last == lsearch || lsearch == "*")){
            //add it to result 
            hold.addCricketer(first, last, vals);
        }
    }
    
    hold.tradeCricketTeams(odResult);
}
