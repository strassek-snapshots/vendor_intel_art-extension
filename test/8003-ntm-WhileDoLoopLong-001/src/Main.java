
// 1 non temporal move expected

public class Main {                                                                                                                                                   
    final int iterations = 0x40000;

    public long checkSum(long[] tab, int n) {
        long s = 0;
        for (int i = 0; i < n ; i++) {
            s = s + tab[i];
        }
        return s;
    }

    public long testLoop(long[] tab) {
        
        int i = 0;
        while (i < iterations) {
            tab[i] = 10L;
            i++;
        }
        return checkSum(tab, iterations);
    }

    public void test()
    {
        long[] tab = new long [iterations];
        System.out.println(testLoop(tab));
    }

    public static void main(String[] args)
    {
        new Main().test();
    }

}  

