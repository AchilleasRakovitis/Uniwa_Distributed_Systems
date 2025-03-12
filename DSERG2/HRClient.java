import java.net.InetAddress;
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class HRClient extends UnicastRemoteObject implements HRInterface{
    
    protected HRClient() throws RemoteException{
        
    }

    public static void main(String[] args)
    {
        try
        {
            //Lookup for the service to oour own registry
            String url = "rmi://" + InetAddress.getLocalHost().getHostAddress() + ":51369/HR";
            Remote lRemote = Naming.lookup(url);
            HRServer lRemoteServer = (HRServer) lRemote;

	    int domatia = 0;
	
            switch (args.length) {									//Emfanish menu client
                case 0:
                case 1:
                    System.out.println("Parametroi:");
                    System.out.println("java HRClient list <hostname>");
                    System.out.println("java HRClient book <hostname> <type> <number> <name>");
                    System.out.println("java HRClient guests <hostname>");
                    System.out.println("java HRClient cancel <hostname> <type> <number> <name>");
                    break;
                case 2:
                    switch (args[0]) {
                        case "list":
                            System.out.println(lRemoteServer.list(args[1]));
                            break;
                        case "guests":
                            System.out.println(lRemoteServer.guests(args[1]));
                            break;
                    }   break;
                case 5:
                    switch (args[0]) {
                        case "book":
                            int total_price = lRemoteServer.book(args[1], args[2], Integer.parseInt(args[3]), args[4]);
                            if(total_price > 0){
                                System.out.println("Ta "+args[3]+" domatia typou "+args[2]+" kraththikan me epityxia me timh " +total_price);                               
                            }else{
                                System.out.println("Yparxoyn mono "+ -total_price +" diathesima domatia tetoiou typoy "+ args[2]);
                                System.out.println("Tha thelate na kanete kratisi mono gia ayta? (Plhktrologiste NAI an thelete allios otidipote allo)");
                                Scanner scan = new Scanner(System.in);
                                String ep = scan.nextLine();
                                if(ep.equalsIgnoreCase("Nai")){
                                    domatia = -total_price;
                                    total_price = lRemoteServer.book(args[1], args[2], -total_price, args[4]);
                                    System.out.println("Ta "+ domatia +" domatia typou "+args[2]+" kraththikan me epityxia me timh " +total_price); 
                                }
                            }

                            break;
                        case "cancel":
                            System.out.println(lRemoteServer.cancel(args[1], args[2], Integer.parseInt(args[3]), args[4]));
                            break;
                    }   break;
                default:
                    break;
            }




        }catch (Exception aInE)
        {
            System.out.println(aInE);
        }
    }
}
