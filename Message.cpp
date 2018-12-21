//============================================================================
// Name        : Message.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Message.h"

Node *Node::get_next(){
	return p_next;
}
std::string Node::get_fragment(){
	return fragment;
}
Node::Node(unsigned int id, std::string frag):identifier{id},fragment{frag},p_next{nullptr}{

};
Message::Message():head{nullptr}{

}
Message::~Message(){
	Node *the_node=head;
	Node *temp=head;
	if(head==nullptr){
		delete head;
	}
	else{
		while(temp->get_next()!=nullptr){
			temp=the_node->get_next();
			delete the_node;
			the_node=temp;
		}
	}
	delete the_node;
	the_node=nullptr;
	temp=nullptr;
	head=nullptr;
}
void Message::insert(unsigned int id,std::string fragment){
	Node *the_node{new Node(id,fragment)};
	if(head==nullptr){
		head=the_node;
	}
	else{
		Node *temp=head;
		//Node *second_last = nullptr;
		if((the_node->identifier)<(temp->identifier)){
			the_node->p_next=temp;
			head=the_node;
		}//if identifier of the_node is smaller than the head identifier
		else{
			if(temp->get_next()==nullptr){
				temp->p_next=the_node;
			}//if reaches the last one in the list, and it is a nullptr, set the next one to equal to the_node
			else{
				while((temp->get_next()!=nullptr)&&(the_node->identifier>temp->get_next()->identifier)&&(temp->get_next()->get_next()!=nullptr)){
					temp=temp->get_next();
				}
				//if the_node identifier is larger than the current identifier, keep moving back

				if((the_node->identifier)<(temp->get_next()->identifier)){
					the_node->p_next=temp->get_next();
					temp->p_next=the_node;
				}//if the_node identifier is smaller than the identifier of the node stored after the current node

				else {
					temp->p_next->p_next=the_node;
				}//if it is bigger, then it goes to the end of the list
			}
		}
	}
}
void Message::print_message(){
	Node *temp=head;
	unsigned int position{0};
	bool isOver{false};
	if(temp==nullptr){
		std::cout<<"???";
	}
	else{
		while(temp->get_next()!=nullptr){
			temp=temp->get_next();
		}
		position=temp->identifier;
		if(temp->get_fragment()=="EOT"){
			isOver=true;
		}
		temp=head;
		for(int i=0;i<=(int)position;i++){
			if(i!=(int)temp->identifier){
				std::cout<<"...";
			}
			else{
				if(temp->get_fragment()!="EOT"){
					std::cout<<temp->get_fragment();
					temp=temp->get_next();
				}

			}
			if(i<(int)position-1){
				std::cout<<" ";
			}
		}
		if(!isOver){
			std::cout<<"???";
		}
	}

}
#ifndef MARMOSET_TESTING
int main() {
	int packet_id{0};
	std::string str{""};
	Message Linked_List;
	bool linked{true};
	while(linked){
		std::cin>>packet_id;
		if(packet_id!=-1&&packet_id!=-2){
			std::cin>>str;
			Linked_List.insert(packet_id,str);
		}
		if(packet_id==-1){
			Linked_List.print_message();
			std::cout<<std::endl;
		}
		if(packet_id==-2){
			linked=false;
		}
	}
	return 0;
}
#endif
