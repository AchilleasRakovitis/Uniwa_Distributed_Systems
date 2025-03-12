struct data {
    int y<>;
    float a;
};

struct apotelesma {
    int minmax<2>;
    float vec<>;
};

program ASKISI1 {
    version ASKISI1_VERS {
        float MO(data) = 1;
        apotelesma MEGEL(data) = 2;
        apotelesma ginom(data) = 3;
    } = 1;
} = 0x234511EF;