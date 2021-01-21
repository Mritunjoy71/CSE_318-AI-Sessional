package testing;

public class User {
    private String name ; 
    private Library library ; 
    private String lend_book;

    public User(String name, Library library) {
        this.name = name;
        this.library = library;
    }
    
    //exception
    public boolean book_lend(Book book){
    	if(book.bookcopy()>0 && book.getLib()==library) {
    		this.lend_book=book.bookname();
    		return true;
    		
    	}
    	
    	
    	return false;
    
    } 
    
    public boolean book_return(Book book){
    	
    	if(lend_book==book.bookname()&& library==book.getLib()) {
    		lend_book="";
    		return true;
    	}
    	return false;

    }

    
}