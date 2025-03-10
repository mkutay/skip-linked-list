public class Main {
	public static void main(String[] args) {
		SkipListPQ<Integer> pq = new SkipListPQ<>(10, 0.5, Integer::compare);
		pq.push(1);
		pq.push(2);
		pq.push(3);
		pq.push(4);
		pq.push(5);
		pq.push(6);
		pq.push(7);
		pq.push(8);
		pq.push(9);
		pq.push(10);
		System.out.println(pq.top());
		System.out.println(pq.getSize());
	}
}
