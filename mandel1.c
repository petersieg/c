int main(int argc, char* argv[]){ unsigned
char c='r';double x1,y,y1,t=0,q=78,r=22,x,
x2,y2,a,b,v;do{(c=='r')?(y2=-(y1=-1.6),x1=
-2.0f,x2=0.8):(c=='?')? c=0,   printf("%f\
,%f:%f,%f",x1,y1,x2,y2):(c     <':'&&c>48)
?x=x1,y=y1,*(c>'3'&&c<':'        ?&y1: &t)
+=(y2-y1)/3,*(c>'6'&&c<            ':'?&y1
:&t)+=(y2-y1)/3, *((c               == '8'
||c+3=='8'||c+3 +3==               '8'?&x1
:&t))+=(x2-x1     )/                3,*((c
=='9'||c+3==                        '9'||c
+6=='9'                          ?&x1: &t)
)+=2*(x2-x1)                        /3,x2=
x1+(x2-x)/3,      y2                 =y1+(
y2-y)/3:(c=0);for(y=                y2;y>=
y1&&c;c=1,y-=(y2-y1)/r,            putchar
('\n')) for(x=x1;x<=x2;            x+=(x2-
x1)/q){a=b=c=0; while  (        ++c&&(a=(t
=a)*a)<4&&(v=b*b)<4)a-=v-x     ,b=y+b*2*t;
putchar("#@XMW*N&KPBQYKG$R"   "STEEVxHOUV"
"CT()[]%JL={}eou?/\\|Ili+~<>_-^\"!;:`,. "[
c?c>>2:63]);}} while((c=getchar ())!='x');
return 0;/* Mandelbrot - S.Goodwin.2001*/}