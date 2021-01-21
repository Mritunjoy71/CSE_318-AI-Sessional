package testing;

public class Library {
    
    
    public String[] booklist=new String[10];
    int count=0;
    // Add a book to the library
    public Book addBook(String name, int num_of_copy){
        Book book = new Book(name, num_of_copy,this);
        this.booklist[count]=name;
        count++;
        return book ; 
    }
    
    
    // Add a user to this library
    public User addUser(String name){
        User user = new User(name,this);
        return user ; 
    }
    
    // Check if this book is available
    public Boolean isAvailable(Book book){
    	for(int i=0;i<10;i++)
    	{
    		if(booklist[i]==book.bookname()) {
    			return true;
    		}
    	}
        return false ; 
    }
    
    
    // return the list of books in the library
    public String[] get_book_list(){
        return booklist ; 
    }
    
}