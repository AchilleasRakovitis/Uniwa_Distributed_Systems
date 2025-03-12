import java.net.InetAddress;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class HRImpl extends UnicastRemoteObject implements HRServer, Runnable
{

    public class Booking {								//Klash gia na kratame tis kratiseis san xexorista antikeimena
        private String type;
        private int number;
        private String name;
        private int totalPrice;

        public Booking(String type, int number, String name, int totalPrice) {
            this.type = type;
            this.number = number;
            this.name = name;
            this.totalPrice = totalPrice;
        }

        // Getters and setters
        public String getType() { return type; }
        public int getNumber() { return number; }
        public void setNumber(int number) { this.number = number; }
        public String getName() { return name; }
        public int getTotalPrice() { return totalPrice; }
        public void setTotalPrice(int totalPrice) { this.totalPrice = totalPrice; }
    }
	
	
    //Orismos listas krathseon kai pliroforion domation
    private List<Booking> bookings = new ArrayList<>();		//List krathseon
    private String[] type = new String[5];				//Typoi domation
    private volatile int[] arithmos = new int[5];			//Arithmos diathesimon
    private int[] price = new int[5];					//Times domation


    protected HRImpl() throws RemoteException {			//Setarisma pliroforion domation
        type[0] = "a";
        type[1] = "b";
        type[2] = "c";
        type[3] = "d";
        type[4] = "e";
        arithmos[0] = 40;
        arithmos[1] = 35;
        arithmos[2] = 25;
        arithmos[3] = 30;
        arithmos[4] = 20;
        price[0] = 75;
        price[1] = 110;
        price[2] = 120;
        price[3] = 150;
        price[4] = 200;
    }

    private int findType(String type){				//Dikh moy methodos gia na brisko ton typo toy domatioy opoy xreiastei
        int apotelesma;
        switch (type.toLowerCase()){
            case "a":
                apotelesma = 0;
                break;
            case "b":
                apotelesma = 1;
                break;
            case "c":
                apotelesma = 2;
                break;
            case "d":
                apotelesma = 3;
                break;
            case "e":
                apotelesma = 4;
                break;
            default:
                apotelesma = -1;
        }
        return apotelesma;
    }


    @Override
    public String list(String host) throws RemoteException{
        String apotelesma = "";
        for (int i = 0; i < 5; i++) {
            apotelesma += arithmos[i] + " τύπου " + type[i] + " -τιμή: " + price[i] + " Ευρώ την βραδιά\n";
        }
        return apotelesma;
    }

    @Override
    public int book(String host, String type, int number, String name) throws RemoteException{
        int total_price;
        int index = findType(type);
        if(arithmos[index] >= number){
            total_price = number * price[index];
            Booking booking = new Booking(type, number, name, total_price);				//Dhmioyrgia neas krathsis
            bookings.add(booking);									//Prosthiki krathsis sto List krathseon
            arithmos[index] -= number;								//Enimerosi diathesimon domation
        }else{
            total_price = arithmos[index] * -1;							//Epistrofi arnitikis timis sto total price, |total_price| = arithmos diathesimon domation
        }
        return total_price;
    }

    @Override
    public String guests(String host) throws RemoteException{		//Gia kathe krathsi stin lista krathseon "grafoyme" sto apotelesma tis plifories krathsis
        String apotelesma = "";
        for (Booking booking : bookings) {
            apotelesma += booking.getName() + " exei kleisei " + booking.getNumber() + " domatia typoy " + booking.getType() + " me synolikh timh " + booking.getTotalPrice() + "\n";
        }
        if(apotelesma.equals("")){
            apotelesma = "Den yparxoyn krathseis akoma.";
        }
        return apotelesma;
    }

    @Override
    public String cancel(String host, String type, int number, String name) throws RemoteException{
        String apotelesma = "";
        int i = 0;
        for (Booking booking : bookings){
            if(booking.getName().equalsIgnoreCase(name) && (booking.getType().equalsIgnoreCase(type)) && booking.getNumber() == number){	//Akyrosi olon ton domation ths krathsis
                bookings.remove(booking);													//Afairesh apo tin lista
                i = 1;
                break;
            }else if (booking.getName().equalsIgnoreCase(name) && (booking.getType().equalsIgnoreCase(type)) && booking.getNumber() > number) {	//Akyrosi ligoteron domation apo to synolo tis kratisis
                booking.setNumber(booking.getNumber() - number);				//Enimerosi krathsis afairontas ta domatia poy akyrothikan
                booking.setTotalPrice(booking.getNumber() * price[findType(type)]);		//Enimerosi krathsis briskontas tin nea timi
                i = 1;
                break;
            }
        }
        if(i == 0){//Den egine akyrosi							
            return apotelesma = "H krathsh den mporese na akyrothei";
        }else {//Egine akyrosi kai enimerosi diathesimon domation
        	arithmos[findType(type)] += number;
        }
        
        for (Booking booking : bookings) {				//Gia kathe booking poy exei idio onoma krathsis me ayto poy molis akirothike mas epistrefei ta ypoloipa bookings toy
            if(booking.getName().equalsIgnoreCase(name)){
                apotelesma += booking.getName() + " exei kleisei " + booking.getNumber() + " domatia typoy " + booking.getType() + " me synolikh timh " + booking.getTotalPrice() + "\n";
            }
        }
        return apotelesma;
    }

    @Override
    public void run()
    {
        
    }

    public static void main(String[] args)
    {
        try
        {
            HRImpl lServer = new HRImpl();
            Registry reg = LocateRegistry.createRegistry(51369);
            String url = "rmi://" + InetAddress.getLocalHost().getHostAddress() + ":51369/HR";


            Naming.rebind(url,lServer);

            Thread lThread = new Thread(lServer);
            lThread.start();
        }
        catch (Exception aInE)
        {
            System.out.println("Remote error- " + aInE);
        }
    }


}
