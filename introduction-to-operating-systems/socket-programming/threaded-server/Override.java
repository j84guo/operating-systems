// dynamic method dispatch is the mechanism by which a call to an overridden method is resolved at runtime
// so a parent/interface reference variables may point to and child object, and the method called is determined at runtime based on the
// object the reference points to
// this is what enables polymorphism

class A {
int i, j;
A(int a, int b) {
i = a;
j = b;
}
// display i and j
void show() {
System.out.println("i and j: " + i + " " + j);
}
}

class B extends A {
int k;
B(int a, int b, int c) {
super(a, b);
k = c;
}
// display k – this overrides show() in A
void show() {
System.out.println("k: " + k);
}
}
class Override {
public static void main(String args[]) {
B subOb = new B(1, 2, 3);
subOb.show(); // this calls show() in B
}
}