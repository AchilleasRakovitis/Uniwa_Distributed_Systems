import java.rmi.Remote;
import java.rmi.RemoteException;

public interface HRServer extends Remote{

    String list(String host) throws RemoteException;

    int book(String host, String type, int number, String name) throws RemoteException;

    String guests(String host) throws RemoteException;

    String cancel(String host, String type, int number, String name) throws RemoteException;
}