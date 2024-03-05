namespace Service1.Service;

public class DataService
{
    public static List<string> FarveListe = new List<string>();
 
    
    public  void GemteFarver()
    {
        FarveListe.Add("RED");
        FarveListe.Add("YELLOW");
        FarveListe.Add("GREEN");
        FarveListe.Add("RED");
        FarveListe.Add("YELLOW");
        FarveListe.Add("GREEN");
        FarveListe.Add("RED");
        FarveListe.Add("YELLOW");
        FarveListe.Add("GREEN");
        
    }

    public  void tilFøjFarve(string farve)
    {
        FarveListe.Add(farve);
    }

   
    public List<string> sendList()
    {
        return FarveListe;
    }
    
    
    
    
    
}