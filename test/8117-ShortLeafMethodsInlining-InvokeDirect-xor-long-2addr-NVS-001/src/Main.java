class Main {
    final static int iterations = 10;

    public static void main(String[] args) {
        Test test = new Test();
        long workJ = 0xFAEFFFAB;
        long workK = 0xF8E9DCBA;

        System.out.println("Initial workJ value is " + workJ);

        for(long i = 0; i < iterations; i++) {
            workJ = test.shim(workJ, workK) + i;
        }

        System.out.println("Final workJ value is " + workJ);
    }
}
