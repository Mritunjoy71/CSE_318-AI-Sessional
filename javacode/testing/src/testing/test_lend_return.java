package testing;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class test_lend_return {

	@Test
	void test1() {
		Library lib=new Library();
		Library lib2=new Library();
		User user =new User("Mritunjoy",lib);
		Book book=new Book("physics",5,lib);
		assertEquals(true,user.book_lend(book) );
	}
	
	@Test
	void test2() {
		Library lib=new Library();
		Library lib2=new Library();
		User user =new User("Mritunjoy",lib);
		Book book=new Book("physics",5,lib);
		user.book_lend(book);
		assertEquals(true,user.book_return(book) );
	}

}
