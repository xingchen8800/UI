#ifndef __XVARIANT_H_
#define __XVARIANT_H_

namespace xc {
    namespace Std {
        class xVariant {
        public:
            xVariant(const char* data);

            template<class Data_t>
            Data_t* GetAs() { return (Data_t*)m_data; }
        private:
            const char* m_data;
        }
    }
}

#endif