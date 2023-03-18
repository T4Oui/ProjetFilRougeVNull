package modele;

import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;

public class BDHistorique {
	
	private Calendar calendar;
	private Map<Object,Integer> mapHistorique = new HashMap<>();
	
	private BDHistorique() {
	}
	
	private static class BDHistoriqueHolder{
		private static final BDHistorique instance = new BDHistorique();
	}
	
	public static BDHistorique getInstance() {
		return BDHistorique.getInstance();
	}
	
	public String visualiserHistorique() {
		String s ="";
		return s;
	}
	
	public void ajouterHistorique(Integer recherche) {
		calendar = calendar.getInstance();
		mapHistorique.put(this.calendar.get(Calendar.MINUTE),recherche);
	}
}
