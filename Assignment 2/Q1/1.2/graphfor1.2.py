import numpy as np
import matplotlib.pyplot as plt

N = 4
fig = np.arange(N)
width = 0.25

SCHED_OTHER_DATA = [3739.147265,3919.690277,3838.981185,3302.763921]
bar1 = plt.bar(fig, SCHED_OTHER_DATA, width, color = 'r')

SCHED_RR_DATA = [2938.981185,3035.698273,2978.746708,2684.928363]
bar2 = plt.bar(fig+width, SCHED_RR_DATA, width, color='g')

SCHED_FIFO_DATA = [2938.746708,3037.703615,2992.273632,2572.263523]
bar3 = plt.bar(fig+width*2, SCHED_FIFO_DATA, width, color = 'b')

plt.xlabel('Thread Priority')
plt.ylabel('Process Time (s)') 
plt.title('Histogram of Process Time For 1.2')

plt.xticks(fig+width,['0  1  2', '0  20  40', '0  80  40' , '0  60  90'])
plt.legend( (bar1, bar2, bar3), ('SCHED_OTHER', 'SCHED_RR', 'SCHED_FIFO') )
plt.show()
