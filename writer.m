#import "writer.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

void copy_to_clipboard(const char *str) {
    @autoreleasepool {
        NSString *nsString = [NSString stringWithUTF8String:str];
        NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
        [pasteboard clearContents];
        [pasteboard writeObjects:@[nsString]];
    }
}