for i in range(11,37): 
    x=8100178706957568
    while x>0:
        if x%i<10:
                x=x/i
        else:break
    if x==0:
        print(i)
# sum=0.00
# for i in range(2,52):
#     sum+=(i-1)*(i-1)/51.0
# print(sum/51)