Thread Kontrol 
---Bu program, C dilinde POSIX thread'leri (pthread) kullanarak işaretleri (signal) kullanarak çoklu thread'leri kontrol etmeyi ve senkronize etmeyi göstermektedir.

Açıklama
---Bu program, belirtilen sayıda işçi (worker) thread'i oluşturur, her biri benzersiz bir numara ile tanımlanır. POSIX thread'leri ve sinyalleri kullanarak bu thread'lerin
yürütmesini kontrol eder. Ana thread, çeşitli sinyalleri dinler ve her işçi thread, ilgili sinyalin etkinleşmesini bekler ve ardından işlemini sürdürür.

Kullanım
---Program, tek bir komut satırı argümanı alır, bu da oluşturulacak işçi thread'lerin sayısıdır. Değer 1 ile 5 arasında olmalıdır. Örneğin, 3 işçi thread'i oluşturmak için şunu çalıştırın:
        ./program 3

Derleme
---Programı derlemek için aşağıdaki komutu kullanın:
        gcc -o program task.c main.c -lpthread

Sinyaller
---Program aşağıdaki sinyallere yanıt verir:
        SIGINT:  1. thread'i etkinleştirir
        SIGTSTP: 2. thread'i etkinleştirir
        SIGUSR1: 3. thread'i etkinleştirir
        SIGUSR2: 4. thread'i etkinleştirir
        SIGQUIT: 5. thread'i etkinleştirir
Bir sinyal alındığında, ilgili thread işlemini sürdürür.