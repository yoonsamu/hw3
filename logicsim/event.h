#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
  bool operator() (Event* first, Event* second) const {
    return (first->time) < (second->time);
  }
} EventLess;
	
#endif