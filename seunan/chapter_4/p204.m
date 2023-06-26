#import <Foundation/Foundation.h>

int main(void) {
    @autoreleasepool {
        // sequential code

        dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

        dispatch_async(queue, ^{
            NSLog(@"I am a block");
        });

        // sequential code

        return 0;
    }
}
