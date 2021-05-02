class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int> maxpq;
    priority_queue<int, vector<int>, greater<int>> minpq;
    int size;
    MedianFinder() {
        size = 0;
    }
    
    void addNum(int num) {
        if(size == 0) maxpq.push(num);
         
        else if(size%2 == 0)
        {
            int num2 = minpq.size() > 0 ? minpq.top(): 0;
            if(num>num2)
            {
               minpq.pop();
               minpq.push(num);
              maxpq.push(num2);
            }
            else 
            {
                maxpq.push(num);
            }
        }
        else 
        {
            int num1 = maxpq.size() > 0 ? maxpq.top() : 0;
            if(num < num1)
            {
                maxpq.pop();
                maxpq.push(num);
                minpq.push(num1);
            }
            else 
            {
                minpq.push(num);
            }
        }
        size++;
    }
    
    double findMedian() {
        if(size == 1)
        {
            return maxpq.top();
        }
        else {
            int num1 = maxpq.size() > 0 ? maxpq.top() : 0, num2 = minpq.size() > 0 ? minpq.top(): 0;;
           // cout << num1 << "  " << num2 << endl;
            if(size%2==0)
            {
                return ((double)(num1+num2)/2);
            } else 
            {
                return num1;
            }
        }
    }
};
