#include <iostream>

using namespace std;

class Computer {
public:
    class CPU {
    public:
        enum CpuRank {
            P1 = 1, P2, P3, P4, P5, P6, P7
        };
    private:
        CpuRank rank;
        int frequency;
        float volage;
    public:
        CPU(CpuRank rank, int frequency, float volage) : rank(rank), frequency(frequency), volage(volage) {}

        void run() {
            cout << "CPU开始运行" << endl;
        }

        CpuRank getRank() const {
            return rank;
        }

        int getFrequency() const {
            return frequency;
        }

        float getVolage() const {
            return volage;
        }

        void stop() {
            cout << "CPU结束运行" << endl;
        }
    };

    class RAM {
    public:
        enum RAM_Type {
            DDR1 = 1, DDR2, DDR3, DDR4
        };
    private:
        int capacity;
        RAM_Type type;
        int bfrequency;
    public:
        RAM(int capacity, RAM_Type type, int bfrequency) : capacity(capacity), type(type), bfrequency(bfrequency) {}

        int getCapacity() const {
            return capacity;
        }

        RAM_Type getType() const {
            return type;
        }

        int getBfrequency() const {
            return bfrequency;
        }

    };

    class CD_ROM {
    public:
        enum INTERFACE_Type {
            SATA = 1, USB
        };
        enum INSTALL_Type {
            external = 1, built_in
        };
        INTERFACE_Type itftype;
        int capacity;
        INSTALL_Type ittype;
    public:
        CD_ROM(INTERFACE_Type itftype, int capacity, INSTALL_Type ittype) : itftype(itftype), capacity(capacity),
                                                                            ittype(ittype) {}
        INTERFACE_Type getItftype() const {
            return itftype;
        }

        int getCapacity() const {
            return capacity;
        }

        INSTALL_Type getIttype() const {
            return ittype;
        }
    };

private:
    CPU cpu;
    RAM ram;
    CD_ROM cd_rom;
public:
    Computer(CPU &cpu, RAM &ram, CD_ROM &cd_rom) : cpu(cpu), ram(ram), cd_rom(cd_rom) {}

    void run() {
        cout << "Computer start running" << endl;
    }

    void stop() {
        cout << "Computer stop running" << endl;
    }

    CPU getCpu() const {
        return cpu;
    }

    RAM getRam() const {
        return ram;
    }

    CD_ROM getCd_rom() const {
        return cd_rom;
    }
};

int main() {
    Computer::CPU cpu(Computer::CPU::CpuRank::P1, 1, 1);
    Computer::RAM ram(1, Computer::RAM::RAM_Type::DDR4, 2);
    Computer::CD_ROM cd_rom(Computer::CD_ROM::INTERFACE_Type::USB, 2, Computer::CD_ROM::INSTALL_Type::external);
    Computer computer(cpu, ram, cd_rom);
    computer.run();
    computer.getCpu().run();
    cout << "cpu,frequency:" << computer.getCpu().getFrequency() << "MHz" << endl;
    cout << "cpu,rank:P" << computer.getCpu().getRank() << endl;
    cout << "cpu,volage:" << computer.getCpu().getVolage() << "V" << endl;
    cout << "ram,capacity:" << computer.getRam().getCapacity() << "MB" << endl;
    cout << "ram,type:DDR" << computer.getRam().getType() << endl;
    cout << "ram,basic frequency:" << computer.getRam().getBfrequency() << "MHz" << endl;
    if (computer.getCd_rom().getItftype() == 1)
        cout << "cd_rom,interface_type:sata" << endl;
    else
        cout << "cd_rom,interface_type:usb" << endl;
    cout << "cd_rom,capcity:" << computer.getCd_rom().getCapacity() << "MB" << endl;
    if (computer.getCd_rom().getIttype() == 1)
        cout << "cd_rom,install_type:exteral" << endl;
    else
        cout << "cd_rom,install_type:built_in" << endl;

    computer.getCpu().stop();
    computer.stop();
}