class Test {
    public float shim(float jj, float ii){
        return simple_method(jj, ii);
    }

    private float simple_method(float jj, float ii) {
        float a = jj;
        a = jj - a;
        a = a - ii;
        return a;
    }

}
