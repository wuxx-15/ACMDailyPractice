#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
enum number {NNULL=1,N2,N3,N4,N5,N6,N7,N8,N9,NT,NJ,NQ,NK,NA};
enum suit {C,D,H,S};
enum CardType {HighCard,Pair,TwoPairs,ThreeOfAKind,Straight,Flush,
FullHouse,FourOfAKind,StraightFlush,RoyalFlush};
class card
{
private:    
    number num;
    suit s;
public:
    card()=default;
    card(int i)
    {
        num=(number)(i/4+2);
        s=(suit)(i%4);
    }
    card(const string& str) 
    {
        switch (str[0])
        {
            case 'T':
                num=NT;
                break;
            case 'J':
                num=NJ;
                break;
            case 'Q':
                num=NQ;
                break;
            case 'K':
                num=NK;
                break;
            case 'A':
                num=NA;
                break;
            default:
                num=(number)(str[0]-'0');
        }
        switch (str[1])
        {
            case 'C':
                s=C;
                break;
            case 'D':
                s=D;
                break;
            case 'H':
                s=H;
                break;
            case 'S':
                s=S;
        }
    }
    number getNumber() const {return num;}
    suit getSuit() const {return s;}
    int getId() {return (num-2)*4+s;}
    friend const bool operator>(const card& c1,const card& c2)
    {
        return c1.num>c2.num;
    }
    friend const bool operator<(const card& c1,const card& c2)
    {
        return c1.num<c2.num;
    }
    friend const bool operator==(const card& c1,const card& c2)
    {
        return c1.num==c2.num;
    }
    friend const bool operator!=(const card& c1,const card& c2)
    {
        return !(c1.num==c2.num);
    }
};
class HandType
{
private:
    card cards[5];
    CardType cType;
    int numberCnt[15];
    number FourKind=NNULL;
    number ThreeKind=NNULL;
    number Pairs[2]={NNULL,NNULL};
    number SingleCard[3]={NNULL,NNULL,NNULL}; //用来判断FoutOfAKind,ThreeOfAKind,Pairs,TwoPairs大小
    int paircnt=0;
    int singlecnt=0;
    bool isFlush() //判断是否是顺子
    {
        return  ( cards[0].getNumber()-cards[1].getNumber()==1 ||
                  cards[0].getNumber()==NA && cards[1].getNumber()==N5 ) &&
                cards[1].getNumber()-cards[2].getNumber()==1 &&
                cards[2].getNumber()-cards[3].getNumber()==1 &&
                cards[3].getNumber()-cards[4].getNumber()==1 ;
    }
    bool isSmallestFlush=false; //用于判断A2345特殊顺子
    int cmp(const HandType& h2) const
    {
        if (cType != h2.cType)
        {
            if (cType > h2.cType) return 1;
            else if (cType < h2.cType) return -1;
        }
        else
        {
            if (cType==FourOfAKind)
            {
                if (FourKind>h2.FourKind) return 1;
                else if (FourKind<h2.FourKind) return -1;
                if (SingleCard[0]>h2.SingleCard[0]) return 1;
                else if (SingleCard[0]<h2.SingleCard[0]) return -1;
                else return 0;
            }
            else if (cType==FullHouse)
            {
                if (ThreeKind>h2.ThreeKind) return 1;
                else if (ThreeKind<h2.ThreeKind) return -1;
                if (Pairs[0]>h2.Pairs[0]) return 1;
                else if (Pairs[0]<h2.Pairs[0]) return -1;
                else return 0;
            }
            else if (cType==ThreeOfAKind)
            {
                if (ThreeKind>h2.ThreeKind) return 1;
                else if (ThreeKind<h2.ThreeKind) return -1;
                else
                {
                    if (SingleCard[0]>h2.SingleCard[0]) return 1;
                    else if (SingleCard[0]<h2.SingleCard[0]) return -1;
                    if (SingleCard[1]>h2.SingleCard[1]) return 1;
                    else if (SingleCard[1]<h2.SingleCard[1]) return -1;
                    return 0;
                }
            }
            else if (cType==TwoPairs)
            {
                if (Pairs[0]>h2.Pairs[0]) return 1;
                else if (Pairs[0]<h2.Pairs[0]) return -1;
                if (Pairs[1]>h2.Pairs[1]) return 1;
                else if (Pairs[1]<h2.Pairs[1]) return -1;
                if (SingleCard[0]>h2.SingleCard[0]) return 1;
                else if (SingleCard[0]<h2.SingleCard[0]) return -1;
                return 0;
            }
            else if (cType==Pair)
            {
                if (Pairs[0]>h2.Pairs[0]) return 1;
                else if (Pairs[0]<h2.Pairs[0]) return -1;
                if (SingleCard[0]>h2.SingleCard[0]) return 1;
                else if (SingleCard[0]<h2.SingleCard[0]) return -1;
                if (SingleCard[1]>h2.SingleCard[1]) return 1;
                else if (SingleCard[1]<h2.SingleCard[1]) return -1;
                if (SingleCard[2]>h2.SingleCard[2]) return 1;
                else if (SingleCard[2]<h2.SingleCard[2]) return -1;
                return 0;
            }
            else if (cType==RoyalFlush) return 0;
            else if (cType==StraightFlush || cType==Straight) 
            {
                if (isSmallestFlush)
                {
                    if (h2.isSmallestFlush) return 0;
                    else return -1;
                }
                else
                {
                    if (h2.isSmallestFlush) return 1; 
                    if (cards[0]>h2.cards[0]) return 1;
                    else if (cards[0]<h2.cards[0]) return -1;
                    return 0;
                }
            }
            else //Flush,HighCard
            {
                for (int i=0;i<5;++i)
                {
                    if (cards[i]>h2.cards[i]) return 1;
                    else if (cards[i]<h2.cards[i]) return -1;
                }
                return 0;
            }
        }
        return 0;
    }
public:
    CardType getType() const {return cType;}
    HandType()=default;
    HandType(const card& c1,const card& c2,const card& c3,
        const card& c4,const card& c5)
    {
        memset(numberCnt,0,sizeof(numberCnt)); //注意初始化
        cards[0]=c1;
        ++numberCnt[c1.getNumber()];
        cards[1]=c2;
        ++numberCnt[c2.getNumber()];
        cards[2]=c3;
        ++numberCnt[c3.getNumber()];
        cards[3]=c4;
        ++numberCnt[c4.getNumber()];
        cards[4]=c5;
        ++numberCnt[c5.getNumber()];
        for (int i=14;i>=2;--i) //降序遍历
        {
            if (numberCnt[i]==2)
            {
                Pairs[paircnt++]=(number)i;
            }
            else if (numberCnt[i]==3)
                ThreeKind=(number)i;
            else if (numberCnt[i]==4)
                FourKind=(number)i;
        }
        sort(cards,cards+5,greater<card>());
        cType=HighCard; //初始化为最低牌型
        //同花
        if (cards[0].getSuit() == cards[1].getSuit() &&
            cards[1].getSuit() == cards[2].getSuit() &&
            cards[2].getSuit() == cards[3].getSuit() &&
            cards[3].getSuit() == cards[4].getSuit() )
        {
            if (isFlush()) 
            {
                if (cards[0].getNumber()==NA) 
                {
                    if (cards[1].getNumber()==NK) cType=RoyalFlush;
                    else 
                    {
                        cType=StraightFlush;
                        isSmallestFlush=true;
                    }
                }
                else cType=StraightFlush;
            }
            else cType=Flush;
        }
        //顺子
        if (isFlush()) 
        {
            cType=max(cType,Straight);
            if (cards[0].getNumber()==NA && cards[1].getNumber()==N5)
                isSmallestFlush=true;
        }
        //对，刻类
        {
            if (FourKind != NNULL) 
            {
                cType=max(cType,FourOfAKind);
                for (int i=0;i<5;++i)
                {
                    if (cards[i].getNumber() != FourKind) 
                        SingleCard[singlecnt++]=cards[i].getNumber();
                }
            }
            else if (ThreeKind != NNULL) 
            {
                if (paircnt==1) cType=max(cType,FullHouse);
                else 
                {
                    cType=max(cType,ThreeOfAKind);
                    for (int i=0;i<5;++i)
                    {
                        if (cards[i].getNumber() != ThreeKind)
                            SingleCard[singlecnt++]=cards[i].getNumber();
                    }
                }
            }
            else if (paircnt>0)
            {
                if (paircnt==2) 
                {
                    cType=max(cType,TwoPairs);
                    for (int i=0;i<5;++i)
                    {
                        if (cards[i].getNumber() != Pairs[0] && cards[i].getNumber() != Pairs[1]) 
                            SingleCard[singlecnt++]=cards[i].getNumber();
                    }
                }
                else 
                {
                    cType=max(cType,Pair);
                    for (int i=0;i<5;++i)
                    {
                        if (cards[i].getNumber() != Pairs[0]) 
                            SingleCard[singlecnt++]=cards[i].getNumber();
                    }
                }
            }
        }
    }
    friend const bool operator>(const HandType& x,const HandType& y)
    {
        return x.cmp(y)==1;
    }
    friend const bool operator<(const HandType& x,const HandType& y)
    {
        return x.cmp(y)==-1;
    }
    friend const bool operator==(const HandType& x,const HandType& y)
    {
        return x.cmp(y)==0;
    }
};
const int CARD_NUM=52;
bool isoccupied[CARD_NUM];
HandType HandTypes[6]; //0,1,2归自己(最优，次优，tmp)，3,4,5归法国人(最优，tmp,抢自己的最优)
card shownCard[8]; //0~3归自己，4～7归法国人
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin>>t;
    string c1,c2,c3,c4;
    string p1,p2,p3,p4;
    while (t--)
    {
        memset(isoccupied,0,sizeof(isoccupied));
        //初始化为最小牌型；
        HandTypes[0]=HandType(card("2S"),card("3S"),card("4S"),card("5S"),card("7C"));
        HandTypes[1]=HandType(card("2S"),card("3S"),card("4S"),card("5S"),card("7C"));
        HandTypes[3]=HandType(card("2S"),card("3S"),card("4S"),card("5S"),card("7C"));
        cin>>c1>>c2>>c3>>c4; //自己的4张明牌
        shownCard[0]=card(c1);
        shownCard[1]=card(c2);
        shownCard[2]=card(c3);
        shownCard[3]=card(c4);
        isoccupied[shownCard[0].getId()]=true;
        isoccupied[shownCard[1].getId()]=true;
        isoccupied[shownCard[2].getId()]=true;
        isoccupied[shownCard[3].getId()]=true;
        cin>>p1>>p2>>p3>>p4;
        shownCard[4]=card(p1);
        shownCard[5]=card(p2);
        shownCard[6]=card(p3);
        shownCard[7]=card(p4);
        isoccupied[shownCard[4].getId()]=true;
        isoccupied[shownCard[5].getId()]=true;
        isoccupied[shownCard[6].getId()]=true;
        isoccupied[shownCard[7].getId()]=true;
        int bestChoice[2];//自己的最优，次优方案
        int antiChoice=-1;//法国人的最优方案
        //法国人决定暗牌
        for (int i=0;i<52;++i)
        {
            if (!isoccupied[i])
            {
                HandTypes[4]=HandType(shownCard[4],shownCard[5],
                    shownCard[6],shownCard[7],card(i));
                if (HandTypes[4]>HandTypes[3])
                {
                    HandTypes[3]=HandTypes[4];
                    antiChoice=i;
                }
            }
        }
        //自己决定暗牌
        for (int i=0;i<52;++i)
        {
            if (!isoccupied[i])
            {
                HandTypes[2]=HandType(shownCard[0],shownCard[1],
                    shownCard[2],shownCard[3],card(i));
                if (HandTypes[2]>HandTypes[0])
                {
                    HandTypes[1]=HandTypes[0];
                    HandTypes[0]=HandTypes[2];
                    bestChoice[1]=bestChoice[0];
                    bestChoice[0]=i;
                }
                else if (HandTypes[2]>HandTypes[1])
                {
                    HandTypes[1]=HandTypes[2];
                    bestChoice[1]=i;
                }
            }
        }
        HandTypes[5]=HandType(shownCard[4],shownCard[5],shownCard[6],
        shownCard[7],card(bestChoice[0]));
        //决战时刻！！！
        /*法国人赢：
            法国人的最优方案优于自己的最优方案（冲突了只能选次优方案）
            或者法国人抢占自己的最优方案后优于自己的次优方案
          自己赢：
            自己的最优方案（冲突了选次优）优于法国人的最优方案
        */
       if (antiChoice==bestChoice[0]) //冲突
       {
            if (HandTypes[3]>HandTypes[1])
                cout<<"GeiWoCaPiXie\n";
            else if (HandTypes[1]>HandTypes[3])
                cout<<"WoYaoYanPai\n";
            else
                cout<<"PaiMeiYouWenTi\n";
       }
       else //不冲突
       {
            if (HandTypes[3]>HandTypes[0] || HandTypes[5]>HandTypes[1])
                cout<<"GeiWoCaPiXie\n";
            else if (HandTypes[0]>HandTypes[3] && HandTypes[1]>HandTypes[5])
                cout<<"WoYaoYanPai\n";
            else
                cout<<"PaiMeiYouWenTi\n";
       }
    }
    return 0;
}
