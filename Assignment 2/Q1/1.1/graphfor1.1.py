import numpy as np
import matplotlib.pyplot as plt

N = 6
fig = np.arange(N)
width = 0.25

SCHED_OTHER_DATA = [22.846608,20.887544,20.347938,9.492472,9.284586,14.484983]
bar1 = plt.bar(fig, SCHED_OTHER_DATA, width, color = 'r')

SCHED_RR_DATA = [19.978158,17.866525,18.304767,8.083599,7.938449,12.576031]
bar2 = plt.bar(fig+width, SCHED_RR_DATA, width, color='g')

SCHED_FIFO_DATA = [19.883530,17.559481,18.236002,8.019555,7.777628,12.928732]
bar3 = plt.bar(fig+width*2, SCHED_FIFO_DATA, width, color = 'b')

plt.xlabel('Thread Priority')
plt.ylabel('Process Time')
plt.title('Histogram Of Process Time For 1.1')

plt.xticks(fig+width,['0  2  3', '0  20  40', '0  40  20' , '0  99  10', '0  69  40', '0  99  99'])
plt.legend( (bar1, bar2, bar3), ('SCHED_OTHER', 'SCHED_RR', 'SCHED_FIFO') )
plt.show()
