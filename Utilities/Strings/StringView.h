#ifndef STRING_VIEW_H_INCLUDED
#define STRING_VIEW_H_INCLUDED

#include <stddef.h>

struct StringView {
    const char *beg_;
    size_t size_;
	
    StringView () = default;
	StringView (const char *str, size_t size);
};

inline StringView make_string_view (const char *beg, size_t size) {
    return StringView { .beg_ = beg, .size_ = size };
}

#endif // STRING_VIEW_H_INCLUDED