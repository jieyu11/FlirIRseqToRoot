#ifndef HASHERDATETIME_H
#define HASHERDATETIME_H
#include "dataDateTime.h"

struct hasherDateTime
{
  std::size_t operator()(const dataDateTime& k) const
  {
    using std::hash;
    using std::size_t;

    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return (
        ((hash<int>()(k.m_year)
          ^ (hash<int>()(k.m_month) << 1)) >> 1)
        ^ ((hash<int>()(k.m_date) 
            ^ (hash<int>()(k.m_hour) << 1)) >> 1)
        ^ ((hash<int>()(k.m_minute) 
            ^ (hash<int>()(k.m_second) << 1)) >> 1)
        );
  }
};

/*
    template <>
      struct hash<dataDateTime>
      {
        std::size_t operator()(const dataDateTime& k) const
        {
          using std::hash;

          // Compute individual hash values for first,
          // second and third and combine them using XOR
          // and bit shifting:

          return (
              ((hash<int>()(k.m_year)
                ^ (hash<int>()(k.m_month) << 1)) >> 1)
              ^ ((hash<int>()(k.m_date) 
                  ^ (hash<int>()(k.m_hour) << 1)) >> 1)
              ^ ((hash<int>()(k.m_minute) 
                  ^ (hash<int>()(k.m_second) << 1)) >> 1)
              );
        }
      };
*/

#endif
