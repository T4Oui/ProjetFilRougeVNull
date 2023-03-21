package modele;

import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;

public class BDHistorique {
	
	private Calendar calendar;
	private Map<String,Map<Recherche,Resultat>> mapHistorique = new HashMap<>();
	
	private BDHistorique() {
	}
	
	private static class BDHistoriqueHolder{
		private static final BDHistorique INSTANCE = new BDHistorique();
	}
	
	public static BDHistorique getInstance() {
		return BDHistoriqueHolder.INSTANCE;
	}
	
	public String visualiserHistorique() {
		return mapHistorique.toString();
	}
	
	public void ajouterHistorique(Recherche recherche,Resultat resultat) {
		calendar = calendar.getInstance();	
		Map<Recherche,Resultat> historique = new HashMap<>();
		historique.put(recherche,resultat);
		String dateHeure = String.valueOf(calendar.get(Calendar.DAY_OF_MONTH)) + "/" + String.valueOf(calendar.get(Calendar.MONTH)) + "/" + "/" + String.valueOf(calendar.get(Calendar.YEAR)) + " " + String.valueOf(calendar.get(Calendar.HOUR_OF_DAY)) +":"+String.valueOf(calendar.get(Calendar.MINUTE)) + ":" + String.valueOf(calendar.get(Calendar.SECOND)) ;
		this.mapHistorique.put(dateHeure,historique);
	}
	
	public static void main(String[] args) {
		BDHistorique bdHistorique = BDHistorique.getInstance();
		bdHistorique.ajouterHistorique(,);
		System.out.println(bdHistorique.visualiserHistorique());
	}
}
