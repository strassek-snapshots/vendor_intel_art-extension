
public class Main {

    // M: was: negative because local_var = field; is not hoisted; lately: positive because LHSS is now before unused loop removal
    // N: positive because local_var = field; is hoisted
    // Test a loop with invariants, which should be hoisted

    int invar0 = 05;
    int invar1 = 15;
    int invar2 = 25;
    int invar3 = 35;
    int invar4 = 45;
    int invar5 = 55;
    int invar6 = 65;
    int invar7 = 75;
    int invar8 = 85;
    int invar9 = 95;
    int invar10 = 17;
    int invar11 = 27;
    int invar12 = 37;
    int invar13 = 47;
    int invar14 = 57;
    int invar15 = 67;

    public int loop() {
        int used0 = 0;
        int used1 = 1;
        int used2 = 2;
        int used3 = 3;
        int used4 = 4;
        int used5 = 5;
        int used6 = 6;
        int used7 = 7;
        int used8 = 8;
        int used9 = 9;
        int used10 = 10;
        int used11 = 10;
        int used12 = 10;
        int used13 = 10;
        int used14 = 10;
       for (int i = 0; i < 10000; i++) {
            used0 = invar0 + invar1;
            used1 = invar1 + invar2 + invar0;
            used2 = invar2 | invar3;
            used3 = invar3 * invar4;
            used4 = invar4 | invar5 & invar4;
            used5 = invar5 - invar6;
            used6 = invar6 + invar7;
            used7 = invar7 - invar8;
            used8 = invar8 * invar9;
            used9 = invar9 - invar10;
            used10 = invar10 + invar11;
            used11 = invar11 - invar12;
            used12 = invar12 | invar13;
            used13 = invar13 - invar14;
            used14 = invar14 | invar15;
        }
        return used0 + used1 + used2 + used3 + used4 + used5 + used6 + used7 + used8 + used9 + used10 + used11 + used12 + used13 + used14;
    }

    public static void main(String[] args) {
        int res = new Main().loop();
        System.out.println(res);
    }
}
