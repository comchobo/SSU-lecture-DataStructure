using namespace std;

int main(){
	Bag<Bizcard> red;
	try{
	cout << "size is "<<red.Size() << endl;
	cout << red.IsEmpty() << endl;
	red.Element().ShowInfo();  // 본래 함수 내에서 try, catch를 하였으나
	cout << endl; 		  // 굳이 그럴 필요가 없어 외부에서 try를 하였다.
}
catch(...)
{
	cout << "error occured"<<endl;
	
}
	Bizcard B("B","12345678");
	Bizcard A("A","12345678");
	Bizcard C("C","12345678");
	red.Push(A);
	red.Push(B);
	red.Push(C);
	try{
	cout << "size is "<<red.Size() << endl;
	cout << red.IsEmpty() << endl;
	red.Element().ShowInfo();
	cout << endl; 
	}
catch(...)
{
	cout << "error occured";	
}
	Bizcard D("D","12345678");
	Bizcard E("E","12345678");
	Bizcard F("F","12345678");
	Bizcard G("G","12345678");
	red.Push(D);
	red.Push(E);
	red.Push(F);
	red.Push(G);

try{
	cout << "size is "<<red.Size() << endl;
	cout << red.IsEmpty() << endl;
	red.Element().ShowInfo();
	cout << endl; 
	}
catch(...)
{ 
	cout << "error occured";	
}
	red.Pop();
	red.Pop();

try{
	cout << "size is "<<red.Size() << endl;
	cout << red.IsEmpty() << endl;
	red.Element().ShowInfo();
	cout << endl; 
	}
catch(...)
{
	cout << "error occured";	
}
	return 0;
}

